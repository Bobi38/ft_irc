#include "Makerj.hpp"
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
	std::cout << " icicici" << std::endl;
	if (rq.size_tab() == 1)
		return client->rcvMsg("461 PASS :Not enough parameters");
	Client* toto;
	toto = server->find_client(rq[1].c_str());
	if (!toto){
		std::cout << " pas trouve de nick equivalent" << std::endl;
		if (!check_name(rq[1].c_str()))
			return client->rcvMsg(":server 777 " + rq[1] + " :Nickname not valiable");	
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

	// if (rq.size_tab() == 6){
	// 	std::string pss(rq[1]);
	// 	size_t i = pss.find_first_of("\r\n", 0);
	// 	pss.erase(i);
	// 	if (pss == server->getPSSD())
	// 		client->setpssd();
	// 	else{
	// 		client->rcvMsg("464 " + client->getNick() + " :Password incorrect");
	// 		server->dlt_client(client, client->getfd());
	// 		return ;
	// 	}
	// 	std::string nick(rq[2]);
	// 	i = nick.find_first_of("\r\n", 0);
	// 	nick.erase(i);
	// 	exec_n(nick, server, client);
	// 	client->setName(rq[3]);
	// 	client->setco();
	// 	return ;
	// }
	std::string ps(rq[1]);
	// if (client->getName() != "" || client->getNick() != ""){
	// 	client->rcvMsg(":server 462 " + client->getNick() + " :You may not reregister");
	// 	return;
	// }
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
	// if (rq.size_tab() == 8){
	// 	client->rcvMsg(":4242 CAP * LS :");
	// 	std::string pss(rq[3]);
	// 	size_t i = pss.find_first_of("\r\n", 0);
	// 	pss.erase(i);
	// 	if (pss == server->getPSSD())
	// 		client->setpssd();
	// 	else{
	// 		client->rcvMsg("464 " + client->getNick() + " :Password incorrect");
	// 		server->dlt_client(client, client->getfd());
	// 		return ;
	// 	}
	// 	std::string nick(rq[4]);
	// 	i = nick.find_first_of("\r\n", 0);
	// 	nick.erase(i);
	// 	exec_n(nick, server, client);
	// 	client->setName(rq[5]);
	// 	client->setco();
	// 	return ;
	// }
	if (rq.size_tab() == 3)
		client->rcvMsg(":4242 CAP * LS :");
}


// bool Client::valid_co(std::string psswd, char* buff, Server *serv){
// 	Client *toto;


// 	if (_nick == "" && _name == "" && strncmp(buff, "PASS ", 5) && _psswd == false){
// 		send_msg(_fd, "we need a nick to connect with command PASS <password>\n");
// 		return true;
// 	}
// 	if (!strncmp(buff, "PASS ", 5) && _psswd == false){
// 		std::string rest(buff + 5);
// 		clean_std(rest);
// 		if ( rest == psswd){
// 			_psswd = true;
// 			return true;
// 		}
// 		else{
// 			send_msg(_fd, "wrong password bye\n");
// 			return false;
// 		}
// 	}
// 	if (_nick == "" && strncmp(buff, "NICK ", 5)){
// 		send_msg(_fd, "we need a nick to connect with command NICK <nickname>\n");
// 		return true;
// 	}
// 	if (!strncmp(buff, "NICK ", 5)){
// 		std::string rest(buff + 5);
// 		clean_std(rest);
// 		toto = serv->find_client(rest);
// 		if (!toto){
// 			_nick = rest;
// 			return true;
// 		}
// 		send_msg(_fd, "NICK already exist, try an over \n");
// 		return true;
// 	}
// 	if (_nick != "" && _name == "" && strncmp(buff, "NAME ", 5)){
// 		send_msg(_fd, "we need a nick to connect with command NICK <nickname>\n");
// 		return true;
// 	}
// 	if (!strncmp(buff, "NAME ", 5)){
// 		std::string rest(buff + 5);
// 		clean_std(rest);
// 		toto = serv->find_client(rest);
// 		if (!toto){
// 			_name = rest;
// 			send_msg(_fd, "welcome to server IRC\n");
// 			_co = true;
// 			return true;
// 		}
// 		send_msg(_fd, "NAME already exist, try an over \n");
// 		return true;
// 	}
// 	return true;

// }