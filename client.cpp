#include <stdio.h>		// printf()
#include <stdlib.h>		// atoi()
#include <string.h>		// strlen()
#include <sys/socket.h>	// socket(), connect()
#include <unistd.h>		// close()

#include "helpers.h"	// make_client_sockaddr()

static const int MAX_MESSAGE_SIZE = 256;

/**
 * Sends a string message to the server and waits for an integer response.
 *
 * Parameters:
 *		hostname: Remote hostname of the server.
 *		port: Remote port of the server.
 * 		message: The message to send.
 * Returns:
 *		The server's response code on success, -1 on failure.
 */
int send_message(const char *hostname, int port, const char *message) {
	if (strlen(message) > MAX_MESSAGE_SIZE) {
		printf("Error: Message exceeds maximum length\n");
		return -1;
	}

	// TODO: Implement the rest of this function

	// (1) Create a socket

	// (2) Create a sockaddr_in to specify remote host and port
	struct sockaddr_in addr;
	if(make_client_sockaddr(&addr, hostname, port) == -1) {
		return -1;
	}

	// (3) Connect to remote server
	
	// (4) Send message to remote server

	// (5) Wait for integer response

	// (6) Close connection

	return -1;
}

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 4) {
		printf("Usage: ./client hostname port_num message\n");
		return 1;
	}
	const char *hostname = argv[1];
	int port = atoi(argv[2]);
	const char *message = argv[3];
	printf("Sending message %s to %s:%d\n", message, hostname, port);

	int response = send_message(hostname, port, message);
	if (response == -1) {
		printf("Error: Failed to send message\n");
		return 1;
	}
	printf("Server responds with status code %d\n", response);
	return 0;
}
