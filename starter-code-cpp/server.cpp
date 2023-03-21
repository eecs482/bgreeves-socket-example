#include <arpa/inet.h>		// htons()
#include <array>
#include <iostream>		// std::cout, std::endl
#include <string>
#include <cstdlib>		// atoi()
#include <sys/socket.h>		// socket(), bind(), listen(), accept(), send(), recv()
#include <unistd.h>		// close()

#include "helpers.h"		// make_server_sockaddr(), get_port_number()

using std::cout;
using std::endl;

static constexpr unsigned int MAX_RECV_SIZE = 1024;

/**
 * Receives a string message from the client and prints it to stdout.
 *
 * Parameters:
 * 		connectionfd: 	File descriptor for a socket connection
 * 				(e.g. the one returned by accept())
 * Returns:
 *		0 on success, -1 on failure.
 */
int handle_connection(int connectionfd) {
	cout << "New connection: " << connectionfd << endl;

	// (1) Receive message from client.

	// (2) Print out the message

	// (3) Close connection

	return 0;
}

/**
 * Endlessly runs a server that listens for connections and serves
 * them _synchronously_.
 *
 * Parameters:
 *		port: 		The port on which to listen for incoming connections.
 *		queue_size: 	Size of the listen() queue
 * Returns:
 *		-1 on failure, does not return on success.
 */
int run_server(int port, int queue_size) {
	// (1) Create socket

	// (2) Set the "reuse port" socket option

	// (3) Create a sockaddr_in struct for the proper port and bind() to it.

	// (3b) Bind to the port.

	// (3c) Detect which port was chosen.

	// (4) Begin listening for incoming connections.

	// (5) Serve incoming connections one by one forever.
}

int main(int argc, const char **argv) {
	// Parse command line arguments
	if (argc != 2) {
		printf("Usage: ./server port_num\n");
		return 1;
	}
	int port = atoi(argv[1]);

	if (run_server(port, 10) == -1) {
		return 1;
	}
	return 0;
}
