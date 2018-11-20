/**
 * This is the really whack part about making sockets. Let me try to explain
 * what is going on here.
 *
 * Unix sockets get bind()-ed to a `sockaddr_in` struct. This struct holds
 * information about where (which network address) the socket will be receiving
 * or sending data to (we think of this as a hostname-port pair).
 * It also holds some other metadata like the socket family.
 *
 * The syntax for working with these sockaddr_in structs is kinda whack.
 * This is just one of those things that you just have to accept 
 * that it works and not question it too much. I'll try to walk you through
 * it with comments to the best of my ability.
 */

#include <arpa/inet.h>	// ntohs()
#include <netdb.h>		// gethostbyname(), struct hostent
#include <netinet/in.h>	// struct sockaddr_in
#include <stdio.h>		// printf()
#include <string.h>		// memcpy()

/**
 * Make a server sockaddr given a port.
 * Parameters:
 *		addr: The sockaddr to modify (this is a C-style function).
 *		port: The port on which to listen for incoming connections.
 * Returns:
 *		0 on success, -1 on failure.
 * Example:
 *		struct sockaddr_in server;
 *		int err = make_server_sockaddr(&server, 8888);
 */
int make_server_sockaddr(struct sockaddr_in *addr, int port) {
	// Step (1): specify socket family.
	// This is an internet socket.
	addr->sin_family = AF_INET;

	// Step (2): specify socket address (hostname).
	// The socket will be a server, so it will only be listening.
	// Let the OS map it to the correct address.
	addr->sin_addr.s_addr = htonl(INADDR_ANY);

	// Step (3): Set the port value.
	// If port is 0, the OS will choose the port for us.
	// Use htons to convert from local byte order to network byte order.
	addr->sin_port = htons(port);

	return 0;
}

/**
 * Make a client sockaddr given a remote hostname and port.
 * Parameters:
 *		addr: The sockaddr to modify (this is a C-style function).
 *		hostname: The hostname of the remote host to connect to.
 *		port: The port to use to connect to the remote hostname.
 * Returns:
 *		0 on success, -1 on failure.
 * Example:
 *		struct sockaddr_in client;
 *		int err = make_client_sockaddr(&client, "141.88.27.42", 8888);
 */
int make_client_sockaddr(struct sockaddr_in *addr, const char *hostname, int port) {
	// Step (1): specify socket family.
	// This is an internet socket.
	addr->sin_family = AF_INET;

	// Step (2): specify socket address (hostname).
	// The socket will be a client, so call this unix helper function
	// to convert a hostname string to a useable `hostent` struct.
	struct hostent *host = gethostbyname(hostname);
	if (host == nullptr) {
		printf("Error: Unknown host %s\n", hostname);
		return -1;
	}
	memcpy(&(addr->sin_addr), host->h_addr, host->h_length);

	// Step (3): Set the port value.
	// Use htons to convert from local byte order to network byte order.
	addr->sin_port = htons(port);

	return 0;
}
