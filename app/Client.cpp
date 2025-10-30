#include "include/Client.hpp"

Client::Client(int fd): _fd(fd), _co(false), _psswd(false), _nick(""), _name(""), _host("127.0.0.1") {}

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

Client::~Client() {
	_chan.clear();
}

int Client::getFd(){
	return _fd;
}

void Client::setNick(const std::string& str){
	if (_nick != "")
		rcvMsg(getMe() + " NICK " + ":" + str);
	_nick = str;
}

void Client::setName(const std::string& str){
	_name = str;
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

void Client::setpssd() {
	if (_psswd == false)
		_psswd = true;
}

void Client::setco() {
	if (_co == false)
		_co = true;
	this->rcvMsg(":server_irc 001 " + _nick + " :Welcome to the IRC Network " + this->getMe());
	this->rcvMsg(":serveur 002 " + _nick + " :Your host is serveur");
	this->rcvMsg(":serveur 376 " + _nick + " :End of /MOTD command.");

}

Channel* Client::getChan(size_t i){
	if (i >= _chan.size())
		return NULL;
	return _chan[i];
}

bool Client::valid_co(std::string psswd, char* buff, Server *serv){
	Client *toto;


	if (_nick == "" && _name == "" && strncmp(buff, "PASS ", 5) && _psswd == false){
		send_msg(_fd, "we need a password to connect with command PASS <password>\n");
		std::cout << " tentative connection mdp bloque\n";
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
		send_msg(_fd, "we need a name to connect with command NAME <nickname>\n");
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
	return (":" + _nick + "!" + _name + "@" + _host );
}

Client::operator bool() const{
	return _co;
}

void Client::deconne(){
	_co = false;
}

void Client::setFd(int x){
	_fd = x;
}
void Client::rcvMsg(const std::string& msg) {
	std::string msg_temp = msg + "\r\n";
	ssize_t sent = send(_fd, msg_temp.c_str(), msg_temp.size(), MSG_NOSIGNAL);
	if (sent < 0) {
		if (errno == EPIPE || errno == ECONNRESET) {
			std::cerr << "Client disconnected" << std::endl;
			// close(_fd);
		}
		else {
			perror("send");
		}
	}
}

void Client::rcvMsg(const std::string& msg, Client* client) {
	std::string msg_temp;
	if (client == NULL)
		return rcvMsg(":server 401 " + getNick()); //(401 : ERR_NOSUCHNICK)
	msg_temp = client->getMe() + " PRIVMSG :" + msg;
	rcvMsg(msg_temp);
}

// void Client::setRealName(std::string realname){
// 	_realname = realname;
// }

// std::string Client::getRealName(){
// 	return _realname;
// }

void Client::print_all_chan(){
	std::cout << getName() << " ";
	for(size_t i = 0; i < _chan.size(); i++){
		std::cout << _chan[i]->getName() << " // ";
	}
	std::cout << std::endl;
}

size_t Client::nbChan(){
	return _chan.size();
}