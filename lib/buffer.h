#ifndef REQPC_BUFFER_H
#define REQPC_BUFFER_H

#include <stdbool.h>
#include <stddef.h>

// A peice of memory + metadata
struct reqpc_buffer {
  size_t used;
  size_t size;
  char *ptr;
};

// Returns the amount of memory left in buffer
size_t reqpc_buffer_mem_left(struct reqpc_buffer *buffer);

// Returns the a pointer to the start of the empty space left in the buffer
char *reqpc_buffer_tail(struct reqpc_buffer *buffer);

// Scales the size of the buffer by factor. Returns true on success and false on
// out of memory.
bool reqpc_buffer_grow(struct reqpc_buffer *buffer, int factor);

// Reads from the file descriptor fd until EOF. Returns true if EOF is reached
// and false if an error occurs.
bool reqpc_buffer_read_until(struct reqpc_buffer *buffer, int fd);

// Create a reqpc_buffer of size initial_size that must be freed by
// reqpc_buffer_free. Returns NULL on out of memory.
struct reqpc_buffer *reqpc_buffer_create(size_t initial_size);

// Frees a reqpc_buffer created by reqpc_buffer_create.
void reqpc_buffer_destroy(struct reqpc_buffer *buffer);

#endif