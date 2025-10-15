#include "include/Server.hpp"
#include "Maker.hpp"

volatile sig_atomic_t stop_server = 0;

Server::Server(const char* password, const char* port): _port(atoi(port)), _password(password)  {
    if (_port < 0 || _port > 65535)
        throw std::runtime_error("Port is not valid");
    _server_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (_server_fd == -1)
        throw std::runtime_error("Socket failed");
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
    if (_server_fd != -1)
        close(_server_fd);
}

void Server::addClient(int fd){
        std::cout <<"ici icic ic " <<std::endl;
    Client* toto = new Client(fd);
    _client.push_back(toto);
}

void Server::addChannel(std::string name, Client* client){
    Channel* toto = new Channel(name, client);
    _chan.push_back(toto);
}

void Server::linkClienttoChannel(Client* client, Channel* channel){
    if (!channel->is_in(client->getName()))
        channel->addClient(client);
    if (!client->is_Channel(channel->getName()))
        client->addChannel(channel);
}

void Server::unlinkClienttoChannel(Client* client, Channel* channel){
    if (channel->is_in(client->getName()))
        channel->rmClient(client);
    if (client->is_Channel(channel->getName()))
        client->rmChannel(channel);
}

void Server::addFd(int fd){
        std::cout <<"lala la la " <<std::endl;
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

void clean_std(std::string& rest){
    for(size_t i = 0; i < rest.size(); i++){
        if (!isprint(rest[i])){
            rest.erase(i, 1);
            i = 0;
        }
    }
}

void handle_sigint(int signum) {
    (void)signum;
    stop_server = 1;
}

// void Server::GoServ(){
//     struct sockaddr_in s, c;
//     socklen_t client_len = sizeof(c);
//     char buffer[512];
//     s.sin_family = AF_INET;
//     s.sin_port = htons(_port);
//     s.sin_addr.s_addr = INADDR_ANY;
//     int opt = 1;
//     if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
//   		throw std::runtime_error("setsocket failed");
//     if (bind (_server_fd, (struct sockaddr *)&s, sizeof(s)) == -1)
//         throw std::runtime_error("Bind failed");
//     if (listen(_server_fd, 100) == -1)
//         throw std::runtime_error("listen failed");

//     std::cout << "server good" << std::endl;
    
//     while(1){
//         if (poll(_fds.data(), _fds.size(), -1) == -1)
//             throw std::runtime_error("poll failed");
//         if (_fds[0].revents & POLLIN){
//                 int nfd = accept(_server_fd, (struct sockaddr *)&c, &client_len);
//                 if (check_psswd(nfd) == true){
//                     addFd(nfd);
//                     addClient(nfd);
//                     std::cout << "new client add " << std::endl;
//                     std::string gg = "welcome to ft_IRC\n";
//                     send(nfd, gg.c_str(), gg.size(), 0);
//                 }
//                 else{
//                 std::cout << "wrong password" << std::endl;
//                 std::string error = "password incorrect boloss\n";
//                 send(nfd, error.c_str(), error.size(), 0);
//                 close (nfd);
//                 }
//             }
//         for (size_t i = 1; i < _fds.size(); ++i) {
//             if (_fds[i].revents & POLLIN) {
//                 int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
//                 std::cout << n << " message = " << buffer << std::endl;
//                 for (size_t j = 1; j < _fds.size(); ++j) {
//                     if (_fds[j].fd != _fds[i].fd)
//                         send(_fds[j].fd, buffer, n, 0);
//                 }
//             }
//         }
//     }
// }

Client* Server::find_fd(int fd){
    for(size_t i = 0; i < _client.size(); i++){
        if (_client[i]->getfd() == fd)
            return _client[i];
    }
    return NULL;
}

void Server::dlt_client(Client* clt, int fd){
        std::cout <<"ici" <<std::endl;
    for(std::vector<Client*>::iterator it = _client.begin(); it != _client.end(); it++){
        if ((*it) == clt){
            _client.erase(it);
            break ;
        }
    }
        std::cout <<"la" <<std::endl;
    close (fd);
        std::cout <<"lo" <<std::endl;
    delete clt;
}

void Server::GoServ(){
	Maker mm;
    struct sockaddr_in s, c;
    socklen_t client_len = sizeof(c);
    char buffer[512];
    s.sin_family = AF_INET;
    s.sin_port = htons(_port);
    s.sin_addr.s_addr = INADDR_ANY;
    int opt = 1;
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  		throw std::runtime_error("setsocket failed");
    if (bind (_server_fd, (struct sockaddr *)&s, sizeof(s)) == -1)
        throw std::runtime_error("Bind failed");
    if (listen(_server_fd, 100) == -1)
        throw std::runtime_error("listen failed");

    std::cout << "server good" << std::endl;
    
    while(stop_server == 0){
        if (poll(_fds.data(), _fds.size(), -1) == -1){
            if (errno == EINTR) continue;
            throw std::runtime_error("poll failed");
        }
        if (_fds[0].revents & POLLIN){
                int nfd = accept(_server_fd, (struct sockaddr *)&c, &client_len);
                addFd(nfd);
                addClient(nfd);
            }
            std::cout <<"1 --- " << _client.size()  <<std::endl;
        for (size_t i = 1; i < _fds.size(); i++) {
                std::cout <<"2" <<std::endl;
            if (_fds[i].revents & POLLIN) {
                memset(buffer, 0, BUFFER_SIZE);
                std::cout <<"3" <<std::endl;
                int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
                std::cout <<"4" <<std::endl;
                Client* tmp = find_fd(_fds[i].fd);
                std::cout <<"5" <<std::endl;
                if (tmp->getco() == false){
                    if (tmp->valid_co(_password, buffer) == false)
                        dlt_client(tmp, _fds[i].fd);
                    break;
                }
                else
                    std::cout << n << " message = " << buffer << std::endl;
				// Request* rq = mm.select(buffer);
				// if (!rq)
                	
				// else
				// 	rq->exec(NULL, &us);
            }
        }
    }
    std::cout << "server down correctly " << std::endl;
}