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
  } else {
    x = 1 << 9;
    int wstatus;
    // waitpid would be useful if we're waiting on a specific process
    // and maybe don't care if/when other child processes finish.
    // or want to  do housekeeping and make sure all child processes
    // finish
    int w = waitpid(rc, &wstatus, 0);
    // int w = wait(NULL);
    assert(rc == w);
    printf("Parent Process (pid:%d), Child Process (pid:%d)\n(wait:%d)\n",
           (int)getpid(), rc, w);
  }
}
