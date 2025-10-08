#include "client.hpp"

// Client::Client(std::string name): _info(_info.push_back(name)) {}

Client::Client(int fd): _fd(fd) {}

Client::~Client() {}

int Client::getFd(){
    return _fd;
}

bool Client::is_Channel(std::string channel){
    for(std::vector<Channel*>::iterator it = _chan.begin(); it != _chan.end(); it++){
        if ((*it)->getName() == channel)
            return true;
    }
    return false;
}

void Client::addChannel(Channel* chan){
    if (!chan->is_Channel(chan->getName()))
        _chan.push_back(chan);
}

void Client::rmChannel(Channel* chan){
    if (!chan)
        return ;
    std::vector<Channel*>::iterator it = find(_chan.begin(), _chan.end(), chan);
    if (it != _chan.end())
        _chan.erase(it);
}

std::string Client::getName(){
    return _name;
}