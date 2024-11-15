#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_IRC_PORT 6667

int main(int ac, char **av) {
	int server_port, server_fd;

	// --> create and config socket 
	server_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (server_fd == -1) {
		std::cerr << "Socket creation failed." << std::endl;
		return EXIT_FAILURE;
	}
	// domain: IPv4 connections format
	// protocol-family: TCP (Transmission Control Protocol)
	// protocol: default one

	if (ac == 2)
		server_port = atoi(av[1]);
	else
		server_port = DEFAULT_IRC_PORT;

	// --> associate socket with a specific network interface and port on your machine
	// (a machine can have several addresses, for instance : ETHERNET, WIFI etc...)
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET; // connections from IPv4 adresses
	server_addr.sin_addr.s_addr = INADDR_ANY; // accept connections on any network interface the machine has
    server_addr.sin_port = htons(server_port); // the port we listen on, turned into a specific format (by htons())
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
		std::cerr << "Socket addressing failed." << std::endl;
		close(server_fd);
		return EXIT_FAILURE;
	}

	if (listen(server_fd, 5) < 0) {  // allow up to 5 pending connections
		perror("Listen failed");
		close(server_fd);
		return 1;
	}
    std::cout << "Server is now listening on port " << server_port << ".\n";

	while (1);
	close(server_fd);
	return EXIT_SUCCESS;
}
