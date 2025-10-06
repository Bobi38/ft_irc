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
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h> 
# include <poll.h>
# include <vector>
# include "client.hpp"

# define BUFFER_SIZE 500

class Server{
    private:
        int _port;
        std::string _password;
        int _server_fd;
        bool    _signal;
        std::vector<Client> _client;
		std::vector<struct pollfd> _fds;
    public:
        Server(const char* password, const char* port);
        void addClient(int fd);
		void addFd(int fd);
        void GoServ();
        ~Server();
	class WrongPort : public std::exception {
		public:
    		virtual const char* what() const throw(){
        		return "Port is not available!";
    		}
    };
	class ErrorSocket : public std::exception {
		public:
    		virtual const char* what() const throw(){
        		return "Error Socket!";
    		}
    };
	class WromgPassword : public std::exception {
		public:
    		virtual const char* what() const throw(){
        		return "Password is not available!";
    		}
	};
};

#endif