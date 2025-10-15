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
# include "Channel.hpp"

class Channel;

class Client{
    private:
        int _fd;
        bool _co;
        std::string _nick;
        std::string _name;
        std::string _host;
        std::vector<Channel*>_chan;
    public:
        Client(int fd);
        Client(const std::string& prefix);
        Client(const Client& other);
        bool valid_co(std::string psswd, char* buff);
        int getFd();
        std::string getName() const;
        int getfd() const ;
        bool getco()const;
        void setNick(const std::string& str);
        void setName(const std::string& str);
        void rmChannel(Channel* chan);
        void addChannel(Channel* chan);
        bool is_Channel(std::string channel);
        ~Client();
};

#endif
