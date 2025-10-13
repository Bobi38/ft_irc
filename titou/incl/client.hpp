#ifndef CLIENT_HPP
# define CLIENT_HPP

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
# include "channel.hpp"

class Channel;

class Client{
    private:
        int _fd;
        std::string _nick;
        std::string _name;
        std::vector<Channel*>_chan;
    public:
        Client(int fd);
        int getFd();
        std::string getName();
        void rmChannel(Channel* chan);
        void addChannel(Channel* chan);
        bool is_Channel(std::string channel);
        ~Client();
};

#endif
