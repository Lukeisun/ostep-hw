#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
  int fd = open("./test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
  write(fd, "swag\n", 5);
  printf("Hello (pid:%d)\n", (int)getpid());
  int rc = fork();
  if (rc < 0) {
    printf("Fork Failed\n");
  } else if (rc == 0) {
    printf("Child Process (pid:%d)\n", (int)getpid());
    char buf[100];
    write(fd, "Child\n", 6);
    printf("%s\n", buf);
  } else {
    write(fd, "Parent\n", 7);
    printf("Parent Process (pid:%d), Child Process (pid:%d)\n", (int)getpid(),
           rc);
  }
}
/*
 * I can write to both with the same file descriptor (couldn't get read to work
 * but i think its a me thing) At least if i wait
 *
 */
