#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <poll.h>
#include <vector>


int main()
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		perror("socket");
		return 1;
	}
	
	sockaddr_in serverAddress;
	std::memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(6667);
	   
	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
  		perror("setsockopt");
   	return 1;
	}

	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		perror("bind");
		return 2;
	}
	
	if (listen(serverSocket, 5) < 0) {
		perror("listen");
		return 3;
	}
	
	std::cout << "Serveur en écoute sur le port 6667..." << std::endl;
	

	std::vector<struct pollfd> fds;
	

	struct pollfd serverPoll;
	serverPoll.fd = serverSocket;
	serverPoll.events = POLLIN;
	fds.push_back(serverPoll);
	
	while (true) {
		int ret = poll(&fds[0], fds.size(), 5000);
		
		if (ret < 0) {
			perror("poll");
			break;
		}
		
		if (ret == 0) {
			std::cout << "Timeout - aucune activité" << std::endl;
			continue;
		}
		
		int MAX_CLIENTS = 2;

		for (size_t i = 0; i < fds.size(); i++) {

			if (fds[i].revents & POLLIN) {
				
				if (fds[i].fd == serverSocket) {
					int clientSocket = accept(serverSocket, NULL, NULL);
					if (clientSocket < 0) {
						perror("accept");
						continue;
					}

					if (fds.size() - 1 < MAX_CLIENTS) {
						struct pollfd clientPoll;
						clientPoll.fd = clientSocket;
						clientPoll.events = POLLIN;
						fds.push_back(clientPoll);
						std::cout << "Nouveau client connecté : " << clientSocket << std::endl;
					} else {
						std::cout << "Nombre maximum de clients atteint" << std::endl;
						close(clientSocket);
					}
				}

				else {
					char buffer[1024];
					int n = recv(fds[i].fd, buffer, sizeof(buffer)-1, 0);
					
					if (n > 0) {
						buffer[n] = '\0';
						std::cout << "Reçu de " << fds[i].fd << " : " << static_cast<int>(buffer[0]) << " : " << static_cast<int>(buffer[1]) << " : " << buffer << std::endl;
						
						const char* msg = "Bien reçu\n";
						send(fds[i].fd, msg, strlen(msg), 0);
					}
					else if (n == 0) {
						std::cout << "Client " << fds[i].fd << " deconnected" << std::endl;
						close(fds[i].fd);
						fds.erase(fds.begin() + i);
						i--;
					}
					else {
						perror("recv");
					}
				}
			}
			
			if (fds[i].revents & (POLLERR | POLLHUP)) {
				std::cout << "Erreur ou déconnexion sur " << fds[i].fd << std::endl;
				close(fds[i].fd);
				fds.erase(fds.begin() + i);
				i--;
			}
		}
	}
	
	for (size_t i = 0; i < fds.size(); i++) {
		close(fds[i].fd);
	}
	
	return 0;
}


