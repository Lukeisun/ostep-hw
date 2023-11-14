#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  int rc = fork();
  if (rc < 0) {
    printf("Call to fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // exec
    char *args[2];
    args[0] = strdup("ls");
    args[1] = NULL;
    // execl("/bin/ls", "ls", "-la", (char *)NULL);
    // p funcs  go off of path, but seems like if you specify
    // absolute dir of binary then it will go off of that
    // Below functions like execl it seeems.
    // execlp("/bin/ls", "ls", "-la", (char *)NULL);
    execlp("ls", "ls", "-la", (char *)NULL);
    // execvp(args[0], args);
  } else {
    printf("Parent did fork\n");
  }
}
// probably so many variants for personal preference
// i'm sure there might be some technical reasons
// as to why you'd pick a p function vs non p.
// but it seems mostly about ergonomics
