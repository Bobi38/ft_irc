#include "client.hpp"

// Client::Client(std::string name): _info(_info.push_back(name)) {}

Client::Client(int fd): _fd(fd) {}

Client::~Client() {}

int Client::getFd(){
    return _fd;
}