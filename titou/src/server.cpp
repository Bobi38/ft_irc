#include "server.hpp"

Server::Server(const char* password, const char* port): _port(atoi(port)), _password(password)  {
    if (_port < 0 || _port > 65535)
        throw WrongPort();
    _server_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (_server_fd == -1)
        throw ErrorSocket();
    addFd(_server_fd);
}

Server::~Server(){
    if (_server_fd != -1)
        close(_server_fd);
}

// void Server::addClient(std::string name){
//     Client toto(name);
//     _client.push_back(toto);
// }

void Server::addClient(int fd){
    Client toto(fd);
    _client.push_back(toto);
}

void Server::addFd(int fd){
    struct pollfd tmp;
    tmp.fd = fd;
    tmp.events = POLLIN;
    _fds.push_back(tmp);
}


void Server::GoServ(){
    struct sockaddr_in s, c;
    socklen_t client_len = sizeof(c);
    char buffer[512];
    s.sin_family = AF_INET;
    s.sin_port = htons(_port);
    s.sin_addr.s_addr = INADDR_ANY;
    int opt = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  		throw std::runtime_error("setsocket failed");
    if (bind (_server_fd, (struct sockaddr *)&s, sizeof(s)) == -1)
        throw std::runtime_error("Bind failed");
    if (listen(_server_fd, 100) == -1)
        throw std::runtime_error("listen failed");

    std::cout << "server good" << std::endl;
    
    while(1){
        if (poll(_fds.data(), _fds.size(), -1) == -1)
            throw std::runtime_error("poll failed");
        if (_fds[0].revents & POLLIN){
            int nfd = accept(_server_fd, (struct sockaddr *)&c, &client_len);
            addFd(nfd);
            addClient(nfd);
        }
        for (size_t i = 1; i < _fds.size(); ++i) {
            if (_fds[i].revents & POLLIN) {
                int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
                std::cout << n << " message = " << buffer << std::endl;
                for (size_t j = 1; j < _fds.size(); ++j) {
                    if (_fds[j].fd != _fds[i].fd)
                        send(_fds[j].fd, buffer, n, 0);
                }
            }
        }
    }
}