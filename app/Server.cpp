#include "include/Server.hpp"
#include "Makerj.hpp"
#include <sstream>

Server::Server(const char* password, const char* port): _port(atoi(port)), _password(password), _ping(time(NULL)), _server_fd(-1)  {
	if (_port < 0 || _port > 65535)
		throw std::runtime_error("  Port is not valid");
	_server_fd = socket (AF_INET, SOCK_STREAM, 0);
	if (_server_fd == -1)
		throw std::runtime_error("  Socket failed");
	addFd(_server_fd);
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
	_client.push_back(toto);
}

Channel* Server::addChannel(std::string name, Client* client){
	Channel* toto = new Channel(name, client);
	_chan.push_back(toto);
	return toto;
}

void Server::linkClienttoChannel(Client* client, Channel* channel){
	if (!channel->is_in(client->getName()))
		channel->addClient(client, PRESENT);
	if (!client->is_Channel(channel->getName()))
		client->addChannel(channel);
}

void Server::unlinkClienttoChannel(Client* client, Channel* channel){
	if (!channel->is_in(client->getName()))
		channel->rmClient(client);
	if (!client->is_Channel(channel->getName()))
		client->rmChannel(channel);
}

void Server::addFd(int fd){
	struct pollfd tmp;
	tmp.fd = fd;
	tmp.events = POLLIN;
	tmp.revents = 0;
	_fds.push_back(tmp);
}

bool Server::check_psswd(int fd){
	char buffer[BUFFER_SIZE];
	std::cout << fd << " test passwd" << std::endl;
	while (1){
		int n = recv(fd, buffer, BUFFER_SIZE, 0);
		buffer[n] = '\0';
		if (!strncmp(buffer, "PASS ", 5))
			break ;
		std::cout << "send the server password with the cmd PASS <password> " << std::endl;
		memset(buffer, 0, sizeof(buffer));
	}
	std::string rest(buffer + 5);
	for(size_t i = 0; i < rest.size(); i++){
		if (!isprint(rest[i])){
			rest.erase(i);
			i = 0;
		}
	}
	if (rest == _password){
		std::cout << "good" << std::endl;
		addClient(fd);
		addFd(fd);
		return true;
	}

	return false;
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

void Server::dlt_client(Client* clt, int fd){
	for(std::vector<Client*>::iterator it = _client.begin(); it != _client.end(); it++){
		if ((*it) == clt){
			_client.erase(it);
			break ;
		}
	}
	std::vector<Channel*> channels_copy;
	for(size_t i = 0; i < clt->nbChan(); i++)
		channels_copy.push_back(clt->getChan(i));

	for(size_t i = 0; i < channels_copy.size(); i++){
		Channel *tmp = channels_copy[i];
		unlinkClienttoChannel(clt, tmp);
		if (tmp->getNbMemb() == 0){
			for(std::vector<Channel*>::iterator it = _chan.begin(); it != _chan.end(); it++){
				if ((*it) == tmp){
					_chan.erase(it);
					break;
				}
			}
			delete tmp;
		}
	}
	std::cout << "on ferme le fd :" <<  fd << std::endl;
	close (fd);
	delete clt;
}

void Server::send_ping(){
	for(size_t i = 0; i < _client.size(); i++){
		std::cout << "msg envoye a =" << _client[i]->getNick() << std::endl;
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
	// throw std::runtime_error(str +" listen failed");
	std::cout << "server good" << std::endl;
	
	while(stop_server == 0){
		for (size_t i = 1; i < _fds.size(); i++){
			_fds[i].events = POLLIN;
			Client* client = find_fd(_fds[i].fd);
			if (client && !client->getBuffOut().empty())
				_fds[i].events |= POLLOUT;
		}
		if (poll(_fds.data(), _fds.size(), 500) == -1){
			if (errno == EINTR) continue;
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
				tmp->write();
			}
			if (_fds[i].revents & POLLIN) {
				memset(buffer, 0, BUFFER_SIZE);
				// std::string next;
				// while (next[next.size() - 1] != '\n' && next[next.size() - 2] != '\r'){
				// 	int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
				// 	std::cout << "n= " << n << " -" << buffer << "----" << std::endl;
				// 	if (n <= 0){
				// 		if (n == 0){
				// 			Client* tmp;
				// 			tmp = find_fd(_fds[i].fd);
				// 			std::string ine = "QUIT";
				// 			mm.select(ine, this, tmp);
				// 			i--;
				// 			break ;
				// 		}
				// 		std::cout << " le fd qui plante : " << _fds[i].fd << std::endl;
				// 		throw std::runtime_error(strerror(errno));
				// 	}
				// 	std::string tmp(buffer);
				// 	std::cout << "--" << tmp << "--" << std::endl;
				// 	next = next + tmp;
				// 	std::cout << static_cast<int>(next[next.size() - 1]) << " " << static_cast<int>(next[next.size() - 2]) << std::endl;
				// 	memset(buffer, 0, BUFFER_SIZE);
				// }
				// std::cout << "out next =" << next << "--" << std::endl;
				int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
				if (n <= 0){
					if (n == 0){
						// Client* tmp;
						// tmp = find_fd(_fds[i].fd);
						std::string ine = "QUIT";
						mm.select(ine, this, tmp);
						i--;
						break ;
					}
					std::cout << " le fd qui plante : " << _fds[i].fd << std::endl;
				}

				// Client* tmp = find_fd(_fds[i].fd);
				std::string next(buffer);
				std::cout << "out =" << next << "--" << std::endl;
				mm.preselect(next, this, tmp);
				// size_t pos;
				// while((pos = next.find("\r\n")) != std::string::npos){
				// 	std::string ine = next.substr(0, pos);
				// 	next.erase(0, pos + 2);
				// 	mm.select(ine, this, tmp);
				// }

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

