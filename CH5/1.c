#include <stdio.h>
#include <stdlib.h>
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
    printf("Child Process (pid:%d) (x:%d)\n", (int)getpid(), x);
  } else {
    x = 1 << 9;
    printf("Parent Process (pid:%d), Child Process (pid:%d)\n(x:%d)\n",
           (int)getpid(), rc, x);
  }
}
/*
 * Changing  x in either process will not affect the result to either Parent or
 * Child As when fork is called the new process is given its own address space
 * It seems as it maybe copies the state of the program some how before as well?
 * Because we are not redclaring x
 */
