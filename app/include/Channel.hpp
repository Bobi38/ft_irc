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
    BAD = -1,
	PRESENT = 1,
    CHANOP = 2,
	NO_PRESENT = 3,
    INVITE = 4,
    BAN = 5,
    BOT ,
    PRIVATE,
    TOPICOP,
    TOPIC_EXIST,
	MOINS,
	PLUS,
    INVITE_ONLY,
    NO_BAN,
	TOPIC,
	KEY,
	LIMIT,
	OPERATOR,
    PILE,
    FACE
};

class Channel{
    private:
        std::string _name;
        std::string _psswrd;
        std::string _topic;
        int _limit;
        bool _topic_exist;
        bool _mode[7];
        std::vector<std::pair<int,Client*> > _member;
    public:
        Channel(std::string name, Client* client);
        std::string getName();
        int getlimit();
        void initt_psswd(std::string psd);
        int getStatutClt(Client* clt);
        std::string getPssd();
        bool is_in(std::string _client_name);
        void addClient(Client* client, int statut);
        void rmClient(Client* Client);
        Client* return_client(std::string _client_name);
        void change_statut(Client* clt, int new_st);
        bool setTopic(std::string topic, Client* sender);
        std::string getTopic();
		void chan_msg(const std::string& msg, Client* sender);
        void whoExec(Client* Client);
        void chan_msg(const std::string& msg, Client* sender, Channel*);
        void chan_msgg(const std::string& msg, Client* sender, std::string send, std::string me);
        void invit(Client* User, Client* Invit);
        bool is_inv(std::string _client_name);
        int getNbMemb();
		Client* getClient(size_t i);
		bool getMODE(int mod) const;
        void chan_msg(const std::string& msg);
        bool setMOD(int mod, Client* user);
        std::pair<int,Client*> getPairC(size_t i);
        void print_all_clt();
        void new_op(std::vector<std::string>::iterator& z, Client* sender, int flag);
        void new_ban(std::vector<std::string>::iterator& z, Client* sender, int flag);
        void init_limit(int sign, Client* clt, std::vector<std::string>::iterator& z);
        void init_psswd(int sign, Client* clt, std::vector<std::string>::iterator& z);
        void mod_op(int sign, Client* clt, std::vector<std::string>::iterator& z);
        void mod_ban(int sign, Client* clt, std::vector<std::string>::iterator& z);
        bool mode_act();
        ~Channel();
};

#endif
