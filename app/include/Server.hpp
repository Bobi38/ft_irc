#ifndef SERVER_HPP
# define SERVER_HPP

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>
# include <fstream>
# include <iomanip>
# include <ctime>
# include <stdexcept>
# include <csignal>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h> 
# include <poll.h>
# include <vector>
# include <algorithm>
# include "Client.hpp"
# include "Channel.hpp"
# include <set>

class Client;
class Channel;


# define BUFFER_SIZE 512 // 512 = max RFC1459 et si ca depasse ?

extern volatile sig_atomic_t stop_server;

void clean_std(std::string &rest);
void handle_sigint(int signum);
void send_msg(int fd, std::string msg);

class Server{
	private:
		int _port;
		std::string _password;
		int _server_fd;
		std::vector<Client*> _client;
		std::vector<struct pollfd> _fds;
		std::vector<Channel*> _chan; // max, nb_user, topic, pwd
	public:
		Server(const char* password, const char* port);
		void addClient(int fd);
		void addChannel(std::string name, Client *client);
		Client* find_fd(int fd);
		void dlt_client(Client* clt, int fd);
		void addFd(int fd);
		void GoServ();
		bool check_psswd(int fd);
		Client* find_client(std::string _nick);
		void linkClienttoChannel(Client* client, Channel* channel);
		void unlinkClienttoChannel(Client* client, Channel* channel);
		~Server();
	class WrongPassword : public std::exception {
		public:
			virtual const char* what() const throw(){
				return "Password is not available!";
			}
	};
};



#endif