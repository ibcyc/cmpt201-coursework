#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter programs to run.\n> ");

    ssize_t num_char = getline(&buff, &size, stdin);
    if (num_char > 0 && buff[num_char - 1] == '\n') {
      buff[num_char - 1] = '\0';
      num_char--;
    }

    pid_t pid = fork();
    if (pid == 0) {
      execl(buff, buff, NULL);
      printf("Exec failure\n");
      exit(1);
    } else {
      waitpid(pid, NULL, 0);
    }
  }

  free(buff);
  return 0;
}
