#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 128

void handle_error(char *error) { _exit(1); }

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  // increase_heap_size
  void *start_address = sbrk(256);

  // initialize_block
  void *block1_address = start_address;
  void *block2_address = (void *)((char *)start_address + 128);

  struct header *h1 = (struct header *)block1_address;
  struct header *h2 = (struct header *)block2_address;

  h1->size = 128;
  h1->next = NULL;
  h2->size = 128;
  h2->next = h1;

  // print for debugging
  print_out("first block:       %p\n", &block1_address, sizeof(block1_address));
  print_out("second block:      %p\n", &block2_address, sizeof(block2_address));
  print_out("first block size:  %lu\n", &h1->size, sizeof(h1->size));
  print_out("first block next:  %p\n", &h1->next, sizeof(h1->next));
  print_out("second block size: %lu\n", &h2->size, sizeof(h2->size));
  print_out("second block next: %p\n", &h2->next, sizeof(h2->next));

  // set to 0 and 1
  size_t header_size = sizeof(struct header);
  size_t data_size = 128 - header_size;
  unsigned char *data1 = (unsigned char *)block1_address + header_size;
  unsigned char *data2 = (unsigned char *)block2_address + header_size;
  memset(data1, 0, data_size);
  memset(data2, 1, data_size);

  // final printing
  for (size_t i = 0; i < data_size; i++) {
    uint64_t value = data1[i];
    print_out("%lu\n", &value, sizeof(value));
  }
  for (size_t i = 0; i < data_size; i++) {
    uint64_t value = data2[i];
    print_out("%lu\n", &value, sizeof(value));
  }

  return 0;
}
