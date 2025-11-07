#include "include/Maker.hpp"

Maker::Maker(){
	table[0] = Level("PASS", exec_pass);
	table[1] = Level("NICK", exec_nick);
	table[2] = Level("USER", exec_user);
	table[3] = Level("QUIT", exec_quit);
	table[4] = Level("JOIN", exec_join);
	table[5] = Level("MODE", exec_Mode);
	table[6] = Level("INVITE", invit);
	table[7] = Level("PRVMSG", prvmsg);
	table[8] = Level("KICK", exec_kick);
	table[9] = Level("LIST", exec_list);
	table[10] = Level("TOPIC", topic);
	table[11] = Level("PING", exec_ping);
	table[12] = Level("PART", exec_part);
	table[13] = Level("PRIVMSG", prvmsg);
	table[14] = Level("WHO", who);
	table[15] = Level("BOT", exec_bot);
	table[16] = Level("bot", exec_bot);
	};

void Maker::preselect(std::string& str, Server* server, Client* client){

	client->setbuff(client->getBuff() + str);
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
	std::string temp = str;
	Request rq(temp);

	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first){
			if (client->getco() == false && i > 3){
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
