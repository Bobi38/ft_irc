#ifndef CHANNEL_HPP
# define CHANNEL_HPP

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
# include "client.hpp"

class Channel{
    private:
        std::string _name;
        int flag;
        std::vector<Client*> _member;
    public:
        Channel(std::string name, Client* client);
        std::string getName();
        bool is_in(std::string _client_name);
        void addClient(Client* client);
        void rmClient(Client* Client);
        void send_msg(std::string msg, int fd);
        ~Channel();
};

#endif
