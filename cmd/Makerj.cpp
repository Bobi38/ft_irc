#include "include/Makerj.hpp"

Maker::Maker(){
	table[0] = Level("PASS", exec_pass);
	table[1] = Level("NICK", exec_nick);
	table[2] = Level("USER", exec_user);
	table[5] = Level("JOIN", exec_join);
	table[3] = Level("CAP", test2);
	table[4] = Level("QUIT", exec_quit);
	table[5] = Level("KICK", exec_kick);
	table[6] = Level("MODE", exec_Mode);
	table[7] = Level("INVITE", invit);
	table[8] = Level("PRVMSG", prvmsg);
	table[9] = Level("KICK", exec_kick);
	table[10] = Level("NAMES", exec_Names);
	table[11] = Level("OPER", test2);
	table[12] = Level("LIST", exec_list);
	table[13] = Level("TOPIC", topic);
	table[14] = Level("PING", exec_ping);
	table[15] = Level("PART", exec_part);
	table[16] = Level("PRIVMSG", prvmsg);
	table[17] = Level("WHO", who);
	};



void Maker::preselect(std::string& str, Server* server, Client* client){
	// std::cout << client->getfd() << "*"  << client->getNick() << " " << str << std::endl;
	// std::cout << "coucou =" << str << "--" << client->getBuff()<< std::endl;

	client->setbuff(client->getBuff() + str);
	std::cout << client->getBuff()[client->getBuff().size() - 1] << " " << client->getBuff()[client->getBuff().size() - 2] << std::endl;
	if (client->getBuff() != "" && client->getBuff()[client->getBuff().size() - 1] != '\n' && client->getBuff()[client->getBuff().size() - 2] != '\r')
		return ;
	std::string next(client->getBuff());
	client->setbuff("");
	size_t pos;
	while((pos = next.find("\r\n")) != std::string::npos){
		std::string ine = next.substr(0, pos);
		next.erase(0, pos + 2);
		select(ine, server, client);
	}
}

void Maker::select(std::string& str, Server* server, Client* client){
	std::cout << client->getfd() << "*"  << client->getNick() << " " << str << std::endl;

	std::string temp = str;
	Request rq(temp);

	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first){
			if (client->getco() == false && i > 4){
				std::cout << ":server_irc 305 : Forbiden Client" << rq.getCmd()  << std::endl;
				return ;
			}
		return table[i].second(rq, server, client);
		}
	}
}

Maker::Maker(const Maker& other) {
	(void) other;
}

Maker* Maker::operator=(const Maker& other){
	(void) other;
	return (this);
}
	
Maker::~Maker() {
}

void test2(Request& rq, Server* server, Client* client){
	(void) rq;
	(void) client;
	(void) server;
	std::cout << "test avec INVITE " << std::endl;
}

void test3(Request& rq, Server* server, Client* client){
	(void) server;
	for (int i = 0; !rq[i].empty(); i++)
		std::cout << rq[i] << " : test avec MODE" << client->getName() << std::endl;
	client->rcvMsg(rq.getMsg());
}