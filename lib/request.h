#ifndef REQPC_REQUEST_H
#define REQPC_REQUEST_H

// A single HTTP header
struct reqpc_header {
  // The key, i.e. Authentication
  char *key;
  // The value assigned to the key
  char *value;
  // The next header, if the header is part of a linked list of headers, else
  // NULL
  struct reqpc_header *next;
};

// An HTTP request
struct reqpc_request {
  // The method i.e. GET, POST, etc.
  char *method;
  // The URL/path of the resource being requested
  char *url;
  // The HTTP request version
  char *version;
  // The HTTP request headers
  struct reqpc_header *headers;
  // The body in binary form (unparsed)
  char *body;
};

// Create a request struct based on the request coming in from clientfd. The
// returned request must be destroyed by reqpc_request_destroy
struct reqpc_request *reqpc_request_create(int clientfd);

// Destroys a reqpc_request struct created by reqpc_request_create
void reqpc_request_free(struct reqpc_request *request);

#endif
