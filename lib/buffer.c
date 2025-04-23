#include "buffer.h"
#include <stdbool.h>
#include <stdlib.h>
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

bool reqpc_buffer_read_until(struct reqpc_buffer *buffer, int fd) {
  int bytes_read;
  // Read until the end of file, or an error
  while ((bytes_read = read(fd, reqpc_buffer_tail(buffer),
                            reqpc_buffer_mem_left(buffer))) > 0) {
    // Update the memory used
    buffer->used += bytes_read;
    if (buffer->used == buffer->size) {
      // If out of space, double the buffer size
      bool success = reqpc_buffer_grow(buffer, 2);
      if (!success)
        return false;
    }
  }
  // Error case
  if (bytes_read == -1)
    return false;

  return true;
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