#include "buffer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t reqpc_buffer_mem_left(struct reqpc_buffer *buffer) {
  return buffer->size - buffer->used;
}

char *reqpc_buffer_tail(struct reqpc_buffer *buffer) {
  return &buffer->ptr[buffer->used];
}

bool reqpc_buffer_grow(struct reqpc_buffer *buffer, int factor) {
  // Reallocate the buffer to new scaled size
  size_t new_size = buffer->size * factor;
  void *new_ptr = realloc(buffer->ptr, new_size);
  if (new_ptr == NULL)
    return false;

  buffer->size = new_size;
  buffer->ptr = new_ptr;

  return true;
}

char *reqpc_buffer_read_until(struct reqpc_buffer *buffer, int fd,
                              char *token) {
  while (true) {
    // Read into the buffer
    char *tail = reqpc_buffer_tail(buffer);
    size_t mem_left = reqpc_buffer_mem_left(buffer);
    int bytes_read = read(fd, tail, mem_left);

    // Return NULL if EOF or error
    if (bytes_read < 0)
      return NULL;

    // If the buffer is now full, double it's size
    if ((buffer->used += bytes_read) >= buffer->size) {
      bool success = reqpc_buffer_grow(buffer, 2);
      if (!success)
        return NULL;
    }

    // Insert the null character so strstr can be used
    tail[bytes_read] = '\0';
    // Search for token in the newly recieved data
    char *token = strstr(tail, token);
    if (token != NULL)
      return token;
  }
}

struct reqpc_buffer *reqpc_buffer_create(size_t initial_size) {
  char *ptr = malloc(initial_size);
  if (ptr == NULL)
    return NULL;

  struct reqpc_buffer *buffer = malloc(sizeof(struct reqpc_buffer));
  if (buffer == NULL)
    return NULL;

  buffer->size = initial_size;
  buffer->ptr = ptr;
  buffer->used = 0;

  return buffer;
}

void reqpc_buffer_free(struct reqpc_buffer *buffer) {
  free(buffer->ptr);
  free(buffer);
}