#include "Maker.hpp"
#include "Channel.hpp"

bool check_name(std::string str){
	if (!isalnum(str[0]))
		return false;
	size_t i = 1;
	for(;i < str.size(); i++){
		if (!isprint(str[i]) || str[i] == ' ')
			return false;
	}
	return true;
}

void exec_nick(Request& rq, Server* server, Client* client){
	if (rq.size_tab() == 1)
		return client->rcvMsg("461 PASS :Not enough parameters");
	Client* toto;
	toto = server->find_client(rq[1].c_str());
	if (!toto){
		if (!check_name(rq[1].c_str()))
			return client->rcvMsg(":server 777 " + rq[1] + " :Nickname not valiable");	
		if (client->getNick() != ""){
			client->rcvMsg(client->getMe() + " NICK :" + rq[1]);
			client->setNick(rq[1].c_str(), server);
			return ;
		}
		client->setNick(rq[1].c_str(), server);
		client->rcvMsg("NICK : " + rq[1]);
		if (!client->getNick().empty() && !client->getName().empty() && client->getpssd())
			client->setco(server);
	}
	else{
		client->deconne();
		client->rcvMsg(":server 433  " + rq[1] + " :Nickname is already in use");
	}
}

void exec_n(std::string name, Server* server, Client* client){
	Client* toto;
	toto = server->find_client(name);
	if (!toto)
		client->setNick(name, server);
	else
		client->rcvMsg(":server 433 : " + name + " Nickname is already in use");
}

void exec_pass(Request& rq, Server* server, Client* client){
	std::string ps(rq[1]);
	if (rq.size_tab() < 2) {
		client->rcvMsg(":server 461 PASS :Not enough parameters");
		return;
	}
	if (ps == server->getPSSD()){
		client->setpssd();
	}else{
		client->rcvMsg(":server 464 " + client->getNick() + " :Password incorrect");
		return ;
	}
	if (!client->getNick().empty() && !client->getName().empty() && client->getpssd())
		client->setco(server);
}

void exec_user(Request& rq, Server* server, Client* client){
	(void)server;
	if (rq.size_tab() == 1)
		return client->rcvMsg(":server 461 PASS :Not enough parameters");
	if (client->getName() != "")
		return client->rcvMsg(":server 462 " + client->getNick() + " :You may not reregister");
	if (!check_name(rq[1].c_str()))
			client->rcvMsg(":server 777 " + rq[1] + " :Nickname not valiable");	
	client->setName(rq[1]);
	if (!client->getNick().empty() && !client->getName().empty() && client->getpssd())
		client->setco(server);
}

void exec_ping(Request& rq, Server* server, Client* client){
	(void)server;
	(void)rq;
	client->rcvMsg(":server PONG server :" + rq[1]);
}

void exec_CAP(Request& rq, Server* server, Client* client){
	(void)server;
	std::cout << "je suis dans CAP" << std::endl;
	if (rq.size_tab() == 3)
		client->rcvMsg(":4242 CAP * LS :");
}
