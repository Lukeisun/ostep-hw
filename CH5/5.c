#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  printf("Hello (pid:%d)\n", (int)getpid());
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    printf("Fork Failed\n");
  } else if (rc == 0) {
    printf("Child Process (pid:%d) (x:%d)\n", (int)getpid(), x);
    x = 1 << 10;
    // wait returns -1 here, an error occured.
    // prob cause theres nothing to wait on
    // errno prints out "No child processes"
    int w = wait(NULL);
    printf("%d\nerr:%s", w, strerror(errno));
    printf("Child Process (pid:%d) (x:%d)\n", (int)getpid(), x);
  } else {
    x = 1 << 9;
    int w = wait(NULL);
    assert(rc == w);
    printf("Parent Process (pid:%d), Child Process (pid:%d)\n(wait:%d)\n",
           (int)getpid(), rc, w);
  }
}
// Wait returns the PID of the child process
