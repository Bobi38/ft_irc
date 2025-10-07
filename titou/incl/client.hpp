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

class Client{
    private:
        int _fd;
        // int _adress;
        std::string _nick;
        std::string _name;
        std::vector<std::pair<std::string, int> > _chan; // is, operator, ban, invit
    public:
        // Client(std::string name);
        Client(int fd);
        int getFd();
        // void write_fd(const std::string& msg);
        // void rmChannel(std::string& channel);
        // void addChannel(std::string& channel);
        int is_Channel(std::string& channel);
        ~Client();
};

#endif
