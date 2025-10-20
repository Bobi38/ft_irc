#include "include/Client.hpp"

Client::Client(int fd): _fd(fd), _co(false), _psswd(false), _nick(""), _name(""), _host("") {}

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
	_host = "localhost";
	_co = true;
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

std::string Client::getNick() const{
    return _nick;
}

Channel* Client::getChan(size_t i){
	if (i >= _chan.size())
		return NULL;
	return _chan[i];
}

bool Client::valid_co(std::string psswd, char* buff, Server *serv){
	Client *toto;


	if (_nick == "" && _name == "" && strncmp(buff, "PASS ", 5) && _psswd == false){
		send_msg(_fd, "we need a nick to connect with command PASS <password>\n");
		return true;
	}
	if (!strncmp(buff, "PASS ", 5) && _psswd == false){
		std::string rest(buff + 5);
		clean_std(rest);
		if ( rest == psswd){
			_psswd = true;
			return true;
		}
		else{
			send_msg(_fd, "wrong password bye\n");
			return false;
		}
	}
	if (_nick == "" && strncmp(buff, "NICK ", 5)){
		send_msg(_fd, "we need a nick to connect with command NICK <nickname>\n");
		return true;
	}
	if (!strncmp(buff, "NICK ", 5)){
		std::string rest(buff + 5);
		clean_std(rest);
		toto = serv->find_client(rest);
		if (!toto){
			_nick = rest;
			return true;
		}
		send_msg(_fd, "NICK already exist, try an over \n");
		return true;
	}
	if (_nick != "" && _name == "" && strncmp(buff, "NAME ", 5)){
		send_msg(_fd, "we need a nick to connect with command NICK <nickname>\n");
		return true;
	}
	if (!strncmp(buff, "NAME ", 5)){
		std::string rest(buff + 5);
		clean_std(rest);
		toto = serv->find_client(rest);
		if (!toto){
			_name = rest;
			send_msg(_fd, "welcome to server IRC\n");
			_co = true;
			return true;
		}
		send_msg(_fd, "NAME already exist, try an over \n");
		return true;
	}
	return true;

}

int Client::getfd()const {
	return _fd;
}

bool Client::getco()const {
	return _co;
}

std::string Client::getMe() const{
	return (":" + _nick + "!" + _name + "@localhost" );
}

Client::operator bool() const{
	return _co;
}

void Client::rcvMsg(const std::string& msg) {
	std::string msg_temp = msg + "\t\n";
	send(_fd, msg_temp.c_str(), msg_temp.size(), 0);
}

void Client::rcvMsg(const std::string& msg, Client* client) {
	std::string msg_temp;
	if (client == NULL)
		return rcvMsg(":server 401 " + getNick()); //(401 : ERR_NOSUCHNICK)
	msg_temp = client->getMe() + " RCVMSG :" + msg + "\t\n";
	send(_fd, msg_temp.c_str(), msg_temp.size(), 0);
}