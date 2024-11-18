#include <poll.h>
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
#define MAX_CLIENTS_NB		5

typedef struct sClient {
	struct sockaddr_in	memoryAdress;
	socklen_t			size;
	char*				ip;
	int					fd;
	int					port;
}	tClient;

typedef struct sServer {
	int					fd;
	int					port;
	struct sockaddr_in	address;

	std::vector<pollfd>		pollfds;
	std::vector<tClient>	clients;
}	tServer;

void disconnectServer(tServer & server) {
	std::vector<pollfd>::iterator	pollfds = server.pollfds.begin();
	++pollfds;

	// Loop through all clients to send a disconnect message and close fd
	for (; pollfds < server.pollfds.end(); ++pollfds) {

		std::string quit_msg = ":localhost QUIT :Server shutting down\n";
		send(pollfds->fd, quit_msg.c_str(), quit_msg.length(), 0);
		close(pollfds->fd);
	}

	close(server.pollfds[0].fd);
	server.clients.clear();
	server.pollfds.clear();
}

int main(int ac, char** av) {
	tServer server;

	// --> create and config socket 
	server.fd = socket(AF_INET, SOCK_STREAM, 0);
	// domain: IPv4 connections format
	// protocol-family: TCP (Transmission Control Protocol)
	// protocol: default one

	if (ac == 2)
		server.port = atoi(av[1]);
	else
		server.port = DEFAULT_IRC_PORT;

	// --> associate socket with a specific network interface and port on your machine
	// (a machine can have several addresses, for instance : ETHERNET, WIFI etc...)
	server.address.sin_family = AF_INET; // connections from IPv4 adresses
	server.address.sin_addr.s_addr = INADDR_ANY; // accept connections on any network interface the machine has
    server.address.sin_port = htons(server.port); // the port we listen on, turned into a specific format (by htons())
	if (bind(server.fd, (struct sockaddr*) &server.address, sizeof(server.address))) {
		perror("Socket addressing failed");
		close(server.fd);
		return EXIT_FAILURE;
	}

	if (listen(server.fd, MAX_CLIENTS_NB) < 0) {
		perror("Listen failed");
		close(server.fd);
		return EXIT_FAILURE;
	}
	std::cout << "Server is now listening clients (" << MAX_CLIENTS_NB << " max) on port " << server.port << std::endl;

	// Add server fd in the poll of fds
	pollfd serverPollfd = {server.fd, POLLIN, 0};
	server.pollfds.push_back(serverPollfd);

	while (server.clients.size() <= MAX_CLIENTS_NB) {
		int ready = poll(server.pollfds.data(), server.pollfds.size(), -1);  // 3rd parameter: timeout
		if (ready > 0) {
			for (size_t i = 0; i < server.pollfds.size(); ++i) {
				if (server.pollfds[i].revents & POLLIN) { // There is something to read
					if (server.pollfds[i].fd == server.fd) { // Read from the server = new client to accept

						tClient newClient;
						newClient.size = sizeof(newClient.memoryAdress);
						memset(&newClient.memoryAdress, 0, newClient.size);

						newClient.fd = accept(server.fd, (struct sockaddr*) &newClient.memoryAdress, &newClient.size);
						if (newClient.fd == -1)
							continue;
						pollfd client_pollfd = {newClient.fd, POLLIN, 0};

						newClient.ip = inet_ntoa(newClient.memoryAdress.sin_addr);
						newClient.port = ntohs(newClient.memoryAdress.sin_port);

						std::cout << "Server accepted a new client:" << std::endl;
						std::cout << "fd: " << newClient.fd << std::endl;
						std::cout << "memoryAdress: " << static_cast<void*>(&newClient.memoryAdress) << std::endl;
						std::cout << "size: " << newClient.size << std::endl;
						std::cout << "ip: " << newClient.ip << std::endl;
						std::cout << "port: " << newClient.port << std::endl << std::endl;

						server.pollfds.push_back(client_pollfd);
						server.clients.push_back(newClient);

						// IRC Handshake Messages
						std::string welcome_msg = ":localhost 001 yournickname :Welcome to the IRC Network\r\n";
						std::string host_msg = ":localhost 002 yournickname :Your host is localhost, running version 1.0\r\n";
						std::string created_msg = ":localhost 003 yournickname :This server was created today\r\n";
						std::string motd_msg = ":localhost 372 yournickname :- Welcome to the server MOTD (Message of the Day)\r\n";
						send(newClient.fd, welcome_msg.c_str(), welcome_msg.length(), 0);
						send(newClient.fd, host_msg.c_str(), host_msg.length(), 0);
						send(newClient.fd, created_msg.c_str(), created_msg.length(), 0);
						send(newClient.fd, motd_msg.c_str(), motd_msg.length(), 0);
					}
					else { // Read from a client
						char buffer[1024];
						ssize_t bytes_read = recv(server.pollfds[i].fd, buffer, sizeof(buffer), 0);

						if (bytes_read <= 0) { // Disconnection message
							close(server.pollfds[i].fd);
							server.clients.erase(server.clients.begin() + i - 1); // -1 because 1st client fd is pollfd[1] but 1st client is clients[0]
							server.pollfds.erase(server.pollfds.begin() + i);

							std::cout << "Client disconnected.\n";

							// Adjust index to avoid skipping next fd
							--i;
						}
						else { // Other messages
							buffer[bytes_read] = '\0';
							std::cout << "Received: " << buffer << std::endl;
						}
					}
				}
			}
		}
	}

	std::cout << "Server is closing..." << std::endl;
	disconnectServer(server);
	return EXIT_SUCCESS;
}

