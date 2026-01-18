#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  while (1) {
    printf("Please enter sometext: ");

    char *buff = NULL;
    size_t size =
        0; // Lab 1 guide mentioned char size = 0. But it seems not working
    ssize_t num_char = getline(&buff, &size, stdin);

    if (num_char == -1) {
      perror("getline failed");
      free(buff);
      exit(EXIT_FAILURE);
    }

    if (buff[0] == '\n') { // Optional Practice - 2
      printf("enter detected");
      free(buff);
      exit(1);
    }

    char *saveptr = NULL;
    char *ret = strtok_r(buff, " ", &saveptr);

    printf("Tokens:\n");

    if (ret != NULL) { // First Line Shouldn't Have \n
      printf("  %s", ret);
      ret = strtok_r(NULL, " ", &saveptr);
    }

    while (ret != NULL) {
      printf("\n  %s", ret);
      ret = strtok_r(NULL, " ", &saveptr);
    }

    free(buff);
  }

  return 0;
}
