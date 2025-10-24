#include "include/Makerj.hpp"

Maker::Maker(): _wClt(NULL) {
	table[0] = Level("PASS", exec_pass);
	table[1] = Level("NICK", exec_nick);
	table[2] = Level("USER", exec_user);
	table[3] = Level("JOIN", exec_join);
	table[15] = Level("PART", exec_part);
	table[5] = Level("KICK", exec_kick);
	table[6] = Level("MODE", mode);
	table[7] = Level("INVITE", invit);
	table[8] = Level("PRVMSG", prvmsg);
	table[9] = Level("QUIT", exec_quit);
	table[10] = Level("NAMES", test2);
	table[11] = Level("OPER", test2);
	table[12] = Level("LIST", exec_list);
	table[13] = Level("TOPIC", topic);
	table[14] = Level("TEST1", test2);
	table[4] = Level("CAP", exec_CAP);
	table[16] = Level("PRIVMSG", prvmsg);

	};

void Maker::select(const std::string& str, Server* server, Client* client){
	std::cout << str << std::endl;
	bool second = (client == _wClt);

	// int size = str.size();
	// if (size < 2 || str[size - 2] != '\r' || str[size - 1] != '\n'){
	// 	std::cout << "demi message " << _buff << std::endl;
	// 	_buff = (second ? _buff + str : str);
	// 	std::cout << "demi message bis " << _buff << std::endl;
	// 	_wClt = client;
	// 	return ;
	// }

	std::string temp = str;
	// temp.resize(size - 2);

	if (second)
		temp = _buff + temp;

	Request rq(temp);

	// std::cout << "creation request avec cmd =" << rq.getCmd() << " " << rq.size_tab() << std::endl;
	// for(int i = 0 ; i < rq.size_tab(); i++)
	// 	std::cout << i << "= " << rq[i] << "->" << std::endl;
	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first){
			if (client->getco() == false && i > 4){
				std::cout << "Client interdit " << rq.getCmd()  << std::endl;
				return ; // retour si client non _co
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