/*
Its like curl without the features. Doesnt support HTTPS and only gets the root of the host.

Just checked valgrind and this has less than 100 allocs. a simple GET request in regular curl
performs 4.5 thousand dynamic mem allocations... i should really make this not suck

Usage: curl <hostname> <port>
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define PACKAGE_NAME "bashmyshell"
#define PROGRAM_NAME "curl"
#define VERSION "0.1"
#define AUTHORS "Micky Lindsay"

// v0.1 Curl but shit. Future improvements:
// * more verbose request construction
// * openssl for secure connections
// * perform 3XX redirects
// * split out the newworking client logic

int main(int argc, char **argv) {
  if (argc < 3) exit(-1);

  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int fd;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* TCP socket */

  if (getaddrinfo(argv[1], "80", &hints, &result) != 0) {
    exit(-1);
  }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if (fd == -1) // Failed to create file descriptor
      continue;
    if (connect(fd, rp->ai_addr, rp->ai_addrlen) == 0) // Successfully connected
      break;
    close(fd); // Cleanup file descriptor on failure
  }

  freeaddrinfo(result);

  if (rp == NULL) {
    exit(-1);
  }

	char buffer[1024];
  int len;

  memset(buffer, 0, 1024);
  len = snprintf(buffer, 1024, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);

  // write HTTP GET request
  write(fd, buffer, len);
  memset(buffer, 0, 1024);

  // read HTTP response
  while (read(fd, buffer, 1023) != 0) {
    fprintf(stdout, "%s", buffer);
    memset(buffer, 0, 1024);
  }

  return 0;
}
