#include "include/Client.hpp"
#include "Request.hpp"

Client::Client(int fd): _fd(fd), _co(false), _psswd(false), _nick(""), _name(""), _buff(""), _host("127.0.0.1") {}

Client::Client(const std::string& prefix) {
	_buff = "";
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

void Client::setNick(const std::string& str, Server* serv){
	if (_nick != "")
		send_all_chan(getMe() + " NICK :" + str, this, serv);
	_nick = str;
}

void Client::setName(const std::string& str){
	_name = str;
	_co = true;
}

void Client::setbuff(std::string newb){
	_buff = newb;
}

std::string Client::getBuff(){
	return _buff;
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

int Client::getfd()const {
	return _fd;
}

bool Client::getco()const {
	return _co;
}

bool Client::getpssd() {
	return _psswd;
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



// void Client::rcvMsg(const std::string& msg) {
// 	std::string msg_temp = msg + "\r\n";
// 	ssize_t sent = send(_fd, msg_temp.c_str(), msg_temp.size(), MSG_NOSIGNAL);
// 	if (sent < 0) {
// 		if (errno == EPIPE || errno == ECONNRESET) {
// 			std::cerr << "Client disconnected" << std::endl;
// 			// close(_fd);
// 		}
// 		else {
// 			perror("send");
// 		}
// 	}
// }

void Client::rcvMsg(const std::string& msg, Client* client) {
	std::string msg_temp = msg;
	if (msg_temp == Request::EMPTY_MSG)
		msg_temp = "";
	if (client == NULL)
		return rcvMsg(":server 401 " + getNick()); //(401 : ERR_NOSUCHNICK)
	msg_temp = client->getMe() + " PRIVMSG : " + msg_temp;
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