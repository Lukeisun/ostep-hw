#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  printf("Hello (pid:%d)\n", (int)getpid());
  // 0 for reading, 1 for writing
  int filedes[2];
  char buf[100];
  int status;
  status = pipe(filedes);
  if (status == -1) {
    printf("Error with pipe");
    exit(1);
  }
  // hmm setting this doesnt seem to cause any errors
  // not sure how to ensure that we read first here...
  // unless i call fork in rc_2, which I'm assuming would
  // result in error if I read->write
  // fcntl(filedes[0], O_NONBLOCK);
  int x = 100;
  int rc = fork();
  int rc_2 = fork();
  // This seems to work but I can't quite wrap my head around it.
  // What happens if we read first? It doesn't seem to fail so
  // is read waiting for something to be in the buffer? It doesn't
  // appear that way because we close the filedescriptor?
  // Actually I just realized that it closes the write filedescriptor
  // in rc_2 but it doesn't mean its closed for rc (because fork copies the
  // filedes arr). So is read just waiting if its called first?
  // Aha reading the manual it does appear to just wait
  // "If some process has the pipe open for writing and O_NONBLOCK is clear,
  // read() shall block the calling thread until some data is written or the
  // pipe is closed by all processes that had the pipe open for writing."
  // And per the pipe man page, O_NONBLOCK is clear
  if (rc < 0 || rc_2 < 0) {
    printf("Fork Failed\n");
  } else if (rc == 0) {
    close(filedes[0]);
    write(filedes[1], "Hello World!\n", 14);
    close(filedes[1]);
    exit(0);
  } else if (rc_2 == 0) {
    close(filedes[1]);
    int nbytes;
    if ((nbytes = read(filedes[0], buf, 100)) < 0) {
      printf("Error reading from pipe: %s", strerror(errno));
    }
    printf("Hello from child process 2! Process 1 Output: %s \n", buf);
    close(filedes[0]);
    exit(0);
  } else {
    int wstatus;
    int w = waitpid(rc_2, &wstatus, 0);
    printf("Parent Process (pid:%d), Child Process (pid:%d)\n", (int)getpid(),
           rc);
  }
}
