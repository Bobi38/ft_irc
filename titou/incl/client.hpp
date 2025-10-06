#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <stdio.h>
# include <stdlib.h>
# include <string>
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

class Client{
    private:
        int _fd;
        int _adress;
        std::vector<std::string> _info;
        std::vector<std::string> _channel;

    public:
        Client(std::string name);
        int getFd();
        void write_fd(const std::string& msg);
        void rmChannel(std::string& channel);
        void addChannel(std::string& channel);
        bool is_Channel(std::string& channel);
        ~Client(){}
};

#endif