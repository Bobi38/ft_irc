#ifndef SERVER_HPP
# define SERVER_HPP

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h> 
# include <poll.h>

class Server{
    private:
        int _port;
        std::string _password;
        bool    _signal;
    public:
        Server();
        Server(std::string password, int port);
        ~Server();
};

#endif