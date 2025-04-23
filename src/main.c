#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

// The default protocol for the other socket parameters
static const int DEFAULT_PROTOCOL = 0;

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

  return EXIT_SUCCESS;
}