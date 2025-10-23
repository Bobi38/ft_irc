#include "Makerj.hpp"
#include "Channel.hpp"
#include <vector>

enum e_mode{
	BAD = -1,
	MOINS,
	PLUS,
	INVITE_ONLY,
	TOPIC,
	KEY,
	LIMIT,
	OPERATOR
}; //= "-+itklo"

int isInStr(char c, std::string& str, int size){
	for(int i = 0; i < size; i++)
		if (str[i] == c)
			return i;
	return BAD;
}

typedef std::pair<char, int> llist;
typedef std::pair<llist, std::string > blist; 
typedef std::vector<blist> vlist;
typedef vlist::iterator vi;

void mode(Request& rq, Server* server, Client* sender){
	int head = 1;
	int arg = 2;
	char sign;
	int mode;
	std::string str = rq[head];
	Channel* Chan;
	Client* Client;
	vlist list;
	if (str[0] == '#' || str[0] == '&'){ // check first param != + ou -
		Chan = server->find_channel(str);
		if (Chan && rq[2].empty())
			return Chan->putMode(sender);
		else
			return sender->rcvMsg(":server 403 :no " + str); //(403 : ERRNOSUCHCHANNEL)
	}
		
	Chan = server->find_channel(str);
	if (Chan && rq[2].empty())
		return sender->rcvMsg(":server 403 :no " + str); //(403 : ERRNOSUCHCHANNEL)
	if (rq[2].empty())
		return Chan->putMode(sender);

	
	
	std::string mod = "-+itklo"; // it sans arg * kl pas d arg si - * o tjrs arg 
	int size = mod.size();
	while (str.empty()){ //parsing
		sign = str[0];
		if (sign != '+' || sign != '-')
			return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS"); // first param != + ou -
		int letter = 1;
		for (; str[letter] != std::string::npos; letter++){
			mode = isInStr(str[letter], mod, size);
			if (mode == BAD)
				return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS"); //mode n existe pas
			llist little;
			little.first = sign;
			little.second = mode;
			blist big;
			big.first = little;
			if (mode == OPERATOR){ //gestion doublon client
				if (rq[arg].empty())
					return sender->rcvMsg (":server 461	ERR_NEEDMOREPARAMS"); // o  sans arg
				Client = server->find_client(rq[arg]);
				if (!Client)
					return sender->rcvMsg (":server 401	" + rq[arg] + " :No such nick/channel");
				for (vi it=list.begin(); it != list.end(); it++)
					if (it->second == rq[arg])
						return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS :too " + str[letter]); // mode doublon
				big.second = rq[arg++];
			}
			else
				for (vi it=list.begin(); it != list.end(); it++)
					if (it->first.second == mode)
						return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS :too " + str[letter]); // mode doublon
			if (sign == '+' && mode >= KEY && mode <= LIMIT){
				if (rq[arg].empty())
					return sender->rcvMsg (":server 461	ERR_NEEDMOREPARAMS"); // l ou k  sans arg
				big.second = rq[arg++];
			}
			else
				big.second = "";
			
			list.push_back(big);
		}
		head = arg + 1;
		str = rq[head];
	}
	for (vi it = list.begin(); it != list.end(); it++){
		sign = it->first.first;
		mode = it->first.second;
		str = it->second;
		if (mode == OPERATOR){
			Client = server->find_client(str);
			if (sign == '+')
				Chan->addClient(Client, OPERATOR);
			else
				Chan->addClient(Client, PRESENT);
		}
		// if (mode <= MOINS)
		// 	Chan->unsetMODEN(mode, sender);
		// else 
		// 	Chan->setMODEN(mode, it->second, sender);
	}
}   // retour mode +o user:serveur MODE #salon +o user1
// void mode(Request& rq, Server* server, Client* sender){
// 	(void) rq;
// 	(void) server;
// 	(void) sender;
// }

void invit(Request& rq, Server* server, Client* sender){
	std::string user = rq[1];
	std::string chan = rq[2];

	if (user.empty() || chan.empty() || !rq[3].empty())
		return sender->rcvMsg(":server 301 "); // attention retour

	Client* User =  server->find_client(user);
	if (!User)
		return sender->rcvMsg(":server 301 :no " + user); //(401 : ERR_NOSUCHNICK)
	Channel* Chan = server->find_channel(chan);
	if (!Chan)
		return sender->rcvMsg(":server 403 :no " + chan); //(403 : ERRNOSUCHCHANNEL)

	std::cout << "test base ok for invit" << std::endl;
	Chan->invit(sender, User);
}

void prvmsg(Request& rq, Server* server, Client* sender){
	if (rq[1].empty())
		return sender->rcvMsg(":server 301 "); // attention retour

	for (int i = 1; !rq[i].empty(); i++){
		std::string dest = rq[i];
		if (dest[0] == '#'|| dest[0] == '&'){
			Channel* Chan = server->find_channel(dest);
			if (!Chan)
				sender->rcvMsg(":server 403 :no " + dest); //(403 : ERRNOSUCHCHANNEL)
			else
				Chan->chan_msg(rq.getMsg(), sender);
		}
		else {
			Client* clrcv = server->find_client(dest);
			if (!clrcv)
				sender->rcvMsg(":server 301 :no " + dest);
			else
				clrcv->rcvMsg(rq.getMsg(), sender);
		}
	}
}

void topic(Request& rq, Server* server, Client* sender){
	std::cout << "/t/tTOPIC" << std::endl;
	std::string chan = rq[1];
	if (chan.empty())
		return sender->rcvMsg(":server 301 "); // attention retour
	std::cout << "first test only TOPIC" << std::endl;
	Channel* Chan= server->find_channel(chan);
	if (!Chan)
		return sender->rcvMsg(":server 403 :" + chan); //(403 : ERRNOSUCHCHANNEL)

	if (rq[MSG].empty() && rq[2].empty()){
		if (Chan->getMOD(TOPIC_EXIST))
			return sender->rcvMsg(":server 331 " + chan + " No topic is set"); //(403 : ERRNOSUCHCHANNEL)
		else
			return sender->rcvMsg(":server 332 " + chan + " :" + Chan->getTopic());
	}	
	std::cout << "test base ok TOPIC" << std::endl;
	if (rq[2].empty()){
		std::cout << "msg = " << rq[MSG] << std::endl;		
		Chan->setTopic(rq[MSG], sender);
	}
	else{
		std::cout << "test TOPIC msg[2]" << std::endl;
		Chan->setTopic(rq[2], sender);
	}
}