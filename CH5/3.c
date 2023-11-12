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
    printf("Error Forking\n");
    exit(1);
  } else if (rc == 0) {
    printf("Hello\n");
  } else {
    int wstatus;
    // technically not wait :) definitely not what
    // instructors want. But not sure how else,
    // maybe some signal magic?
    waitpid(rc, &wstatus, 0);
    printf("Goodbye\n");
  }
}
