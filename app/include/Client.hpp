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
# include "Server.hpp"

class Server;

class Channel;

class Client{
	private:
		int _fd;
		bool _co;
		bool _psswd;
		std::string _nick;
		std::string _name;
		std::string _buff;
		std::string _outBuff;
		std::string _host;
		std::vector<Channel*>_chan;
	public:
		Client();
		Client(int fd);
		Client(const std::string& prefix);
		Client(const Client& other);
		int getFd();
		void setbuff(std::string newb);
		std::string getBuff();
		std::string getName() const;
		std::string getNick() const;
		std::string getMe() const;
		std::string& getBuffOut();
		Channel* getChan(size_t i);
		int getfd() const;
		bool getco()const;
		void setNick(const std::string& str, Server* serv);
		void setName(const std::string& str);
		void rmChannel(Channel* chan);
		void addChannel(Channel* chan);
		bool is_Channel(std::string channel);
		void print_all_chan();
		void setpssd();
		bool getpssd();
		void setco(Server* serv);
		void deconne();
		void addBuffOut(std::string& str);
		void write();
		void rcvMsg(const std::string& str, Client* sender);
		void rcvMsg(const std::string& str);
		size_t nbChan();
		~Client();
};

#endif
