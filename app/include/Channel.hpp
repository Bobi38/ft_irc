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
	PRESENT,
    CHANOP,
	NO_PRESENT,
    INVITE,
    BAN,
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
	OPERATOR
};


class Channel{
    private:
        std::string _name;
        std::string _psswrd;
        std::string _topic;
        int _limit;
        bool _topic_exist;
        bool _mode[6];
        std::vector<std::pair<int,Client*> > _member;
    public:
        Channel(std::string name, Client* client);
        std::string getName();
        int getStatutClt(Client* clt);
        std::string getPssd();
        void init_psswd(std::string psswd);
        bool is_in(std::string _client_name);
        void addClient(Client* client, int statut);
        void rmClient(Client* Client);
        Client* return_client(std::string _client_name);
        void change_statut(Client* clt, int new_st);
        void setTopic(std::string topic, Client* sender);
        std::string getTopic();
		void chan_msg(const std::string& msg, Client* sender); //envoie un message a tous les connecte
        void whoExec(Client* Client);
        void chan_msg(const std::string& msg, Client* sender, Channel*); //envoie un message a tous les connecte
        void invit(Client* User, Client* Invit);
        int getNbMemb();
		Client* getClient(size_t i);
		bool getMODE(int mod) const;
		static std::string str_mode;
        void chan_msg(const std::string& msg);
        bool setMOD(int mod, Client* user);
        std::pair<int,Client*> getPairC(size_t i);
        void print_all_clt();
        void new_op(std::string clt, Client* sender, int flag);
        void init_limit(std::string limit);
        void new_ban(std::string clt, Client* sender, int flag);
        ~Channel();
};

#endif
