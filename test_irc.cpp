#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#define DEFAULT_IRC_PORT	6667
#define MAX_CLIENTS_NB		3

typedef struct sClient {
	int					fd;
	struct sockaddr_in	memoryAdress;
	socklen_t			size;

	char				*ip;
	int					port;
}	client;

void disconnectClients(std::vector<client *> &clients) {
	// Loop through all connected clients and send a disconnect message
	for (size_t i = 0; i < clients.size(); ++i) {
		client *currentClient = clients[i];

		// Send a "QUIT" message or any other disconnect message
		std::string quit_msg = ":localhost QUIT :Server shutting down\n";
		send(currentClient->fd, quit_msg.c_str(), quit_msg.length(), 0);

		// Close the client's socket
		close(currentClient->fd);

		// Free the memory used by the client object
		delete currentClient;
	}
	// Clear the clients vector
	clients.clear();
}

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
		perror("Socket addressing failed");
		close(server_fd);
		return EXIT_FAILURE;
	}


	if (listen(server_fd, MAX_CLIENTS_NB) < 0) {
		perror("Listen failed");
		close(server_fd);
		return 1;
	}
	std::cout << "Server is now listening clients (" << MAX_CLIENTS_NB << " max) on port " << server_port << std::endl;

	std::vector<client *> clients;
	while (clients.size() <= MAX_CLIENTS_NB) {
		client *newClient = new client;
		newClient->size = sizeof(newClient);
		newClient->fd = accept(server_fd, (struct sockaddr*)&newClient->memoryAdress, &newClient->size);
		if (newClient->fd != -1) {
			memset(&newClient->memoryAdress, 0, newClient->size);
			std::string connection_msg = ":localhost 001 yournickname :Welcome to the IRC Network";

			newClient->ip = inet_ntoa(newClient->memoryAdress.sin_addr);
    		newClient->port = ntohs(newClient->memoryAdress.sin_port);

			clients.push_back(newClient);

			std::cout << "Server accepted a new client:" << std::endl;
			std::cout << "fd: " << newClient->fd << std::endl;
			std::cout << "memoryAdress: " << static_cast<void*>(&newClient->memoryAdress) << std::endl;
			std::cout << "size: " << newClient->size << std::endl;
			std::cout << "ip: " << newClient->ip << std::endl;
			std::cout << "port: " << newClient->port << std::endl;

			// ssize_t bytes_sent = send(newClient->fd, connection_msg.c_str(), connection_msg.length(), 0);
		}
		else
			delete newClient;
	}

	disconnectClients(clients);
	close(server_fd);
	std::cout << "Server is closing..." << std::endl;
	return EXIT_SUCCESS;
}
