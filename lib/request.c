#include "request.h"
#include <stdlib.h>

struct reqpc_request *reqpc_request_create(int clientfd) {
  struct reqpc_request *request = malloc(sizeof(struct reqpc_request));
  if (request == NULL)
    return NULL;

  return request;
}

void reqpc_request_destroy(struct reqpc_request *request) { free(request); }