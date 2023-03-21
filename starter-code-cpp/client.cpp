#include <arpa/inet.h> // ntohs()
#include <iostream>
#include <cstdlib> // atoi()
#include <string>
#include <sys/socket.h> // socket(), connect(), send(), recv()
#include <unistd.h>     // close()

#include "helpers.h" // make_client_sockaddr()

using std::cout;
using std::endl;

static constexpr unsigned int MAX_SEND_SIZE = 1024;

/**
 * Sends a string message to the server.
 *
 * Parameters:
 *		hostname: 	Remote hostname of the server.
 *		port: 		Remote port of the server.
 * 		message: 	The message to send, as a C-string.
 * Returns:
 *		0 on success, -1 on failure.
 */
int send_message(const char *hostname, int port, std::string &message) {
  // (1) Create a socket

  // (2) Create a sockaddr_in to specify remote host and port

  // (3) Connect to remote server

  // (4) Send message to remote server

  // (5) Close connection

  return 0;
}

int main(int argc, const char **argv) {
  // Parse command line arguments
  if (argc != 4) {
    cout << "Usage: ./client hostname port_num message" << endl;
    return 1;
  }
  const char *hostname = argv[1];
  int port = atoi(argv[2]);
  std::string message(argv[3]);

  cout << "Sending message " << message << " to " << hostname << ':' << port
       << endl;
  if (send_message(hostname, port, message) == -1) {
    return 1;
  }

  return 0;
}
