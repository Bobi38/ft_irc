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

typedef std::vector<std::pair<int,Client*> > C_Client;
typedef C_Client::iterator cci;

enum e_client{
    PRESENT,
    CHANOP,
    INVITE,
    BAN,
    PRIVATE,
    TOPICOP,
    TOPIC_EXIST
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
        size_t getNbMemb();
        bool get_i();
        int getStatutClt(Client* clt);
        std::string getPssd();
        void init_psswd(std::string psswd);
        bool is_in(std::string _client_name);
        void addClient(Client* client);
        void rmClient(Client* Client);
		bool getMOD(int mod) const;
		std::string getTopic() const;
		void setMOD(int mod, Client* sender); //par mod = -TOPIC_EXIST for unactiv et mod = TOPIC_EXIST pour activ
        void setTopic(std::string topic, Client* sender);
        // void send_msg(std::string msg, int fd);
		void chan_msg(const std::string& msg, Client* sender); //envoie un message a tous les connecte
		Client* getClient(size_t i);
        ~Channel();
};

#endif
