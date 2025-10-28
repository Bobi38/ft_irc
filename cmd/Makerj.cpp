#include "include/Makerj.hpp"

Maker::Maker(){
	table[0] = Level("PASS", exec_pass);
	table[1] = Level("NICK", exec_nick);
	table[2] = Level("USER", exec_user);
	table[3] = Level("JOIN", exec_join);
	table[4] = Level("CAP", exec_CAP);
	table[5] = Level("KICK", exec_kick);
	table[6] = Level("MODE", exec_Mode);
	table[7] = Level("INVITE", invit);
	table[8] = Level("PRVMSG", prvmsg);
	table[9] = Level("QUIT", exec_quit);
	table[10] = Level("NAMES", test2);
	table[11] = Level("OPER", test2);
	table[12] = Level("LIST", exec_list);
	table[13] = Level("TOPIC", topic);
	table[14] = Level("TEST1", test2);
	table[15] = Level("PART", exec_part);
	table[16] = Level("PRIVMSG", prvmsg);
	table[17] = Level("WHO", who);
	};

void Maker::select(std::string& str, Server* server, Client* client){
	std::cout << str << std::endl;

	std::string temp = str;
	Request rq(temp);

	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first){
			if (client->getco() == false && i > 4){
				std::cout << ":server_irc 305 : Forbiden Client" << rq.getCmd()  << std::endl;
				return ;
			}
		std::cout << "creation request avec cmd =" << rq.getCmd() << std::endl;
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
	std::cout << "test avec INVITE " << server->check_psswd(5) << std::endl;
}

void test3(Request& rq, Server* server, Client* client){
	(void) server;
	for (int i = 0; !rq[i].empty(); i++)
		std::cout << rq[i] << " : test avec MODE" << client->getName() << std::endl;
	client->rcvMsg(rq.getMsg());
}