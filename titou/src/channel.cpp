#include "channel.hpp"

Channel::Channel(std::string name, Client* client): _name(name), flag(0) {
    if (client)
        _member.push_back(client);
}

std::string Channel::getName(){
    return _name;
}

bool Channel::is_in(std::string _client_name){
    for(std::vector<Client*>::iterator it = _member.begin(); it != _member.end(); it++){
        if ((*it)->getName() == _client_name)
            return true;
    }
    return false;
}

void Channel::addClient(Client* client){
    if (!client->is_Channel(client->getName()))
        _member.push_back(client);
}

void Channel::rmClient(Client* client){
    if (!client)
        return ;
    std::vector<Client*>::iterator it = find(_member.begin(), _member.end(), client);
    if (it != _member.end())
        _member.erase(it);
}

Channel::~Channel(){
    _member.clear();
}