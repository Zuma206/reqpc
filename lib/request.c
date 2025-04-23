#include "request.h"
#include "buffer.h"
#include <stdlib.h>

struct reqpc_request *reqpc_request_create(int clientfd) {
  struct reqpc_buffer *buffer = malloc(sizeof(struct reqpc_buffer));
  if (buffer == NULL)
    return NULL;

  struct reqpc_request *request = malloc(sizeof(struct reqpc_request));
  if (request == NULL)
    return NULL;

  request->buffer = buffer;

  return request;
}

void reqpc_request_destroy(struct reqpc_request *request) {
  reqpc_buffer_free(request->buffer);
  free(request);
}