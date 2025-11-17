#include "include/Server.hpp"
#include "Maker.hpp"
#include <sstream>

Server::Server(const char* password, const char* port): _port(atoi(port)), _password(password), _ping(time(NULL)), _server_fd(-1)  {
	for (int i = 0; port[i]; i++)
		if (!isdigit(port[i]) || i > 9)
			throw std::runtime_error("  Port is not valid");
	if (_port < 1024 || _port > 65535)
		throw std::runtime_error("  Port is not valid");
	if (!check_psd(_password))
		throw std::runtime_error("  Password not valid");
	_server_fd = socket (AF_INET, SOCK_STREAM, 0);
	if (_server_fd == -1)
		throw std::runtime_error("  Socket failed");
	addFd(_server_fd);
}


bool Server::check_psd(std::string password){
	bool icpt = false;
	bool tcpt = false;

	if (password.size() < 4)
		return false ;
	for(size_t i = 0; i < password.size(); i++){
		if (isdigit(password[i]) && !icpt)
			icpt = true;
		if (isupper(password[i]) && !tcpt)
			tcpt = true;
	}
	if (!icpt || !tcpt)
		return false;
	return true;
}

Server::~Server(){
	for(std::vector<Client*>::iterator it = _client.begin(); it != _client.end(); it ++)
		delete *it;
	for(std::vector<Channel*>::iterator it = _chan.begin(); it != _chan.end(); it ++)
		delete *it;
	for(size_t i = 1; i < _fds.size(); i++)
		close(_fds[i].fd);
	_fds.clear();
	_client.clear();
	_chan.clear();
	if (_server_fd != -1){
		std::cout << "close fd server" << std::endl;
		close(_server_fd);
	}
}

void Server::addClient(int fd){
	Client* toto = new Client(fd);
	Bot* bot = dynamic_cast<Bot *>(find_client("bot"));
	_client.push_back(toto);
	bot->addClient(toto);
}

Channel* Server::addChannel(std::string name, Client* client){
	Channel* toto = new Channel(name, client);
	_chan.push_back(toto);
	return toto;
}

void Server::linkClienttoChannel(Client* client, Channel* channel){
	if (!channel->is_in(client->getNick()))
		channel->addClient(client, PRESENT);
	if (!client->is_Channel(channel->getName()))
		client->addChannel(channel);
}

bool Server::unlinkClienttoChannel(Client* client, Channel* channel){
	if (channel->is_in(client->getNick()) || channel->is_inv(client->getNick()))
		channel->rmClient(client);
	else
		return true ;
	if (client->is_Channel(channel->getName()))
		client->rmChannel(channel);
	if (channel->getNbMembb() == 0){
		for(std::vector<Channel*>::iterator it = _chan.begin(); it != _chan.end(); it ++){
			if (*it == channel){
				Channel* tmp = *it;
				_chan.erase(it);
				delete tmp;
				return false;
			}
		}
	}
	return true;
}

void Server::dlt_client(Client* clt, int fd){
	Bot* bot = dynamic_cast<Bot *>(find_client("bot"));
	bot->rmClient(clt);
	for(std::vector<Client*>::iterator it = _client.begin(); it != _client.end(); it++){
		if ((*it) == clt){
			_client.erase(it);
			break ;
		}
	}
	for(size_t i = 0; i < _chan.size();){
		if (!unlinkClienttoChannel(clt, _chan[i]))
			continue ;
		i++;
	}
	close (fd);
	delete clt;
}

void Server::addFd(int fd){
	struct pollfd tmp;
	tmp.fd = fd;
	tmp.events = POLLIN;
	tmp.revents = 0;
	_fds.push_back(tmp);
}


Client* Server::find_client(std::string _nick){
	if (_nick == "")
		return NULL;
	for(size_t i = 0; i < _client.size(); i++){
		if (_nick == _client[i]->getNick() || _nick == _client[i]->getName())
			return _client[i];
	}
	return NULL;
}

Channel* Server::find_channel(std::string chan){
	if (chan.empty())
		return NULL;
	for(size_t i = 0; i < _chan.size(); i++){
		if (chan == _chan[i]->getName()){
			return _chan[i];
		}
	}
	return NULL;
}

std::string Server::getPSSD(){
	return _password;
}

Client* Server::find_fd(int fd){
	for(size_t i = 0; i < _client.size(); i++){
		if (_client[i]->getfd() == fd)
			return _client[i];
	}
	return NULL;
}



void Server::send_ping(){
	for(size_t i = 0; i < _client.size(); i++){
		_client[i]->rcvMsg("PING 4242");
	}
}

void Server::GoServ(){
	std::ostringstream os;
	os << _server_fd;
	std::string str = os.str();
	Maker mm;
	struct sockaddr_in s, c;
	socklen_t client_len = sizeof(c);
	char buffer[BUFFER_SIZE];
	s.sin_family = AF_INET;
	s.sin_port = htons(_port);
	s.sin_addr.s_addr = INADDR_ANY;
	int opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  		throw std::runtime_error(str +" setsocket failed");
	if (bind (_server_fd, (struct sockaddr *)&s, sizeof(s)) == -1)
		throw std::runtime_error(str +" Bind failed");
	if (listen(_server_fd, 100) == -1)
		throw std::runtime_error(str +" listen failed");
	std::cout << "server good" << std::endl;
	Client* bot = new Bot();
	_client.push_back(bot);
	while(stop_server == 0){
		for (size_t i = 1; i < _fds.size(); i++){
			_fds[i].events = POLLIN;
			Client* client = find_fd(_fds[i].fd);
			if (client && !client->getBuffOut().empty()){
				std::cout << "bu =-----" << client->getBuffOut() << "----------" << client->getFd() << std::endl;
				_fds[i].events |= POLLOUT;
			}
		}
		if (poll(_fds.data(), _fds.size(), 500) == -1){
			if (errno == EINTR) {
				continue;
			}
			throw std::runtime_error(str + " poll failed");
		}
		if (_fds[0].revents & POLLIN){
				int nfd = accept(_server_fd, (struct sockaddr *)&c, &client_len);
				addFd(nfd);
				addClient(nfd);
			}
		for (size_t i = 1; i < _fds.size(); i++) {
			Client* tmp = find_fd(_fds[i].fd);
			if (!tmp)
				continue ;
			if (_fds[i].revents & POLLOUT){
				std::cout << "in bucle =-----" << tmp->getBuffOut() << "-------" << tmp->getFd() << std::endl;
				tmp->write();
			}
			if (_fds[i].revents & POLLIN) {
				memset(buffer, 0, BUFFER_SIZE);

				int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
				if (n <= 0){
					if (n == 0){
						std::string ine = "QUIT";
						mm.select(ine, this, tmp);
						i--;
						break ;
					}
					std::cout << " error f : " << _fds[i].fd << std::endl;
				}
				std::string next(buffer);
				mm.preselect(next, this, tmp);
			}
		}
	}
	std::cout << "server down correctly " << std::endl;
}


Channel* Server::getSChan(size_t i){
	if (i >= _chan.size())
		return NULL;
	return _chan[i];
}

size_t Server::sizeChan(){
	return _chan.size();
}

