#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

// The default protocol for the other socket parameters
static const int DEFAULT_PROTOCOL = 0;

// Port to bind to
static const int PORT = 4321;

// The amount of clients to queue before denying connections
static const int BACKLOG = 3;

// Print the error message to stderr and exit if the assertion is false
void assert(bool assertion, char *error) {
  if (assertion)
    return;
  fprintf(stderr, "%s.\n", error);
  exit(EXIT_FAILURE);
}

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
  assert(sockfd != -1, "Failed to create a socket");

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);

  int status = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  assert(status != -1, "Failed to bind socket to a port");

  status = listen(sockfd, BACKLOG);
  assert(status != -1, "Failed to listen on the socket");

  while (true) {
    int clientfd = accept(sockfd, NULL, NULL);
  }

  return EXIT_SUCCESS;
}