#include <arpa/inet.h>		// ntohs()
#include <iostream>
#include <string>
#include <stdlib.h>		// atoi()
#include <sys/socket.h>		// socket(), connect(), send(), recv()
#include <unistd.h>		// close()

#include "helpers.h"		// make_client_sockaddr()

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
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// (2) Create a sockaddr_in to specify remote host and port
	sockaddr_in addr{};
	if (make_client_sockaddr(&addr, hostname, port) == -1) {
		return -1;
	}

	// (3) Connect to remote server
	if (connect(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
		perror("Error connecting stream socket");
		return -1;
	}
	
	// (4) Send message to remote server
	// Call send() enough times to send all the data
	ssize_t sent = 0;
	do {
		ssize_t n = send(sockfd, message.c_str() + sent, message.length() - sent, 0);
		if (n == -1) {
			perror("Error sending on stream socket");
			return -1;
		}
		sent += n;
	} while (sent < message.length());

	// (5) Close connection
	close(sockfd);

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

	cout << "Sending message " << message << " to " << hostname << ':' << port << endl;
	if (send_message(hostname, port, message) == -1) {
		return 1;
	}

	return 0;
}
