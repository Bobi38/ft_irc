#include "./include/Channel.hpp"

Channel::Channel(std::string name, Client* client): _name(name), _limit(-1), _i_private(false), _t_topicop(false), _topic_exist(false) {
    if (client){
        std::pair<int , Client*> tt (CHANOP, client);
        _member.push_back(tt);
    }
}

std::string Channel::getName(){
    return _name;
}

bool Channel::is_in(std::string _client_name){
    for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
        if (it->second->getName() == _client_name)
            return true;
    }
    return false;
}

void Channel::addClient(Client* client){
    if (!client->is_Channel(client->getName())){
        std::pair<int , Client*> tt (PRESENT, client);
        _member.push_back(tt);
    }
}

void Channel::rmClient(Client* client){
    if (!client)
        return ;
    for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
        if (it->second == client){
            _member.erase(it);
            break;
        }
    }
}

Channel::~Channel(){
    _member.clear();
}