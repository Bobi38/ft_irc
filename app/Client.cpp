#include "include/Client.hpp"

Client::Client(int fd): _fd(fd), _co(false) {}

Client::Client(const std::string& prefix) {
	size_t size = prefix.size();
	size_t space = prefix.find(" ");

	if (prefix.empty() || prefix[0] != ':' || size == 1) {
		_nick = "";
		_name = "";
		_host = "";
		return;
	}
	
	size_t start = 1;
	size_t end = prefix.find("!", start);
	
	if (end == std::string::npos || end >= space) {
		end = (space != std::string::npos) ? space : size;
		_nick = prefix.substr(start, end - start);
		_name = "";
		_host = "";
		return;
	}
	
	_nick = prefix.substr(start, end - start);
	
	start = end + 1;
	end = prefix.find("@", start);
	
	if (end == std::string::npos || end >= space) {
		_name = "";
		_host = "";
		return;
	}

	_name = prefix.substr(start, end - start);
	
	start = end + 1;
	end = (space != std::string::npos) ? space : size;
	_host = prefix.substr(start, end - start);
}

Client::Client(const Client& other) : _fd(other._fd), \
		_nick(other._nick), _name(other._name), _host(other._host) {}

Client::~Client() {}

int Client::getFd(){
    return _fd;
}

void Client::setNick(const std::string& str){
    _nick = str;
}

void Client::setName(const std::string& str){
    _name = str;
}

bool Client::is_Channel(std::string channel){
    for(std::vector<Channel*>::iterator it = _chan.begin(); it != _chan.end(); it++){
        if ((*it)->getName() == channel)
            return true;
    }
    return false;
}

void Client::addChannel(Channel* chan){
    if (!chan->is_in(chan->getName()))
        _chan.push_back(chan);
}

void Client::rmChannel(Channel* chan){
    if (!chan)
        return ;
    std::vector<Channel*>::iterator it = find(_chan.begin(), _chan.end(), chan);
    if (it != _chan.end())
        _chan.erase(it);
}

std::string Client::getName() const{
    return _name;
}