#include "request.h"
#include "buffer.h"
#include <stdlib.h>

struct reqpc_request *reqpc_request_create(int clientfd) {
  struct reqpc_buffer *buffer = reqpc_buffer_create(8);
  if (buffer == NULL)
    return NULL;

  struct reqpc_request *request = malloc(sizeof(struct reqpc_request));
  if (request == NULL) {
    reqpc_buffer_free(buffer);
    return NULL;
  }
  request->buffer = buffer;

  request->method = reqpc_buffer_tail(buffer);
  char *first_space = reqpc_buffer_read_until(buffer, clientfd, " ");
  if (first_space == NULL) {
    reqpc_request_free(request);
    return NULL;
  }
  *first_space = '\0';

  return request;
}

void reqpc_request_free(struct reqpc_request *request) {
  reqpc_buffer_free(request->buffer);
  free(request);
}