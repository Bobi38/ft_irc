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
# include <vector>
# include <utility>
# include "Client.hpp"
# include "Server.hpp"

class Client;

enum e_client{
    PRESENT,
    CHANOP,
    INVITE,
    BAN
};

class Channel{
    private:
        std::string _name;
        std::string _psswrd;
        std::string _topic;
        int _limit;
        bool _i_private;
        bool _t_topicop;
        bool _topic_exist;
        std::vector<std::pair<int,Client*> > _member;
    public:
        Channel(std::string name, Client* client);
        std::string getName();
        bool is_in(std::string _client_name);
        void addClient(Client* client);
        void rmClient(Client* Client);
        void send_msg(std::string msg, int fd);
        Client* getClient(size_t i);
        ~Channel();
};

#endif
