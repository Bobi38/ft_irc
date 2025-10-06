#include "server.hpp"

# define BUFFER_SIZE 1024

Server::Server(const char* password, const char* port): _port(atoi(port)), _password(password)  {
    if (_port < 0 || _port > 65535)
        throw WrongPort();
    _server_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (_server_fd == -1)
        throw ErrorSocket();
}

Server::~Server(){
    if (_server_fd != -1)
        close(_server_fd);
}

// void Server::addClient(std::string name){
//     Client toto(name);
//     _client.push_back(toto);
// }

void Server::GoServ(){
    struct sockaddr_in s, c;
    socklen_t client_len = sizeof(c);
    char buffer[BUFFER_SIZE];
    s.sin_family = AF_INET;
    s.sin_port = htons(_port);
    s.sin_addr.s_addr = INADDR_ANY;
    if (bind (_server_fd, (struct sockaddr *)&s, sizeof(s)) == -1)
        throw std::runtime_error("Bind failed");
    if (listen(_server_fd, 100) == -1)
        throw std::runtime_error("listen failed");
    _signal = true;
    std::cout << "server good" << std::endl;
    
    int client_fd = accept(_server_fd, (struct sockaddr *)&c, &client_len);

        std::cout << "server accept ..." << std::endl;
        // 6. Recevoir un message
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("recv");
    } else {
        buffer[bytes_received] = '\0';
        printf("Message reçu : %s\n", buffer);

        // 7. Répondre au client
        const char *response = "Bonjour depuis le serveur !";
        send(client_fd, response, strlen(response), 0);
    }

    close (client_fd);
}