#include "Makerj.hpp"
#include "Channel.hpp"

// bool isInStr(char c, std::string& str, int size){
// 	for(int i = 0; i < size; i++)
// 		if (str[i] == c)
// 			return true;
// 	return false;
// }

// bool defSign(std::string& str, int pos){
// 	for( ; pos >= 0; pos--){
// 		if (str[pos] = '+')
// 			return true;
// 		if (str[pos] = '-')
// 			return false;
// 	}
// 	return true;
// }

// void mode(Request& rq, Server* server, Client* sender){
// 	int head = 1;
// 	std::string str = rq[head];
// 	Channel* Chan;
// 	Client* Client;
// 	if (str[0] == '#' || str[0] == '&'){
// 		Chan = server->find_channel(str);
// 		if (Chan && rq[2].empty())
// 			return Chan->putMod(sender);
// 		else
// 			return sender->rcvMsg(":server 403 :no " + str); //(403 : ERRNOSUCHCHANNEL)
// 	}
		
// 	Chan = server->find_channel(str);
// 	if (Chan && rq[2].empty())
// 		return sender->rcvMsg(":server 403 :no " + str); //(403 : ERRNOSUCHCHANNEL)
// 	if (rq[2].empty())
// 		return Chan->putMod(sender);
	
// 		std::string mod = "+-itkol";
// 	int size = mod.size();
// 	while (str.empty()){
// 		if (str[0] != '+' && str[0] != '-')
// 			return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS");
// 		int letter = 1;
// 		for (; str[letter] != std::string::npos; letter++)
// 			if (!isInStr(str[letter], mod, size))
// 				return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS");
// 		if (str[--letter] != '+' && str[letter] != '-')
// 			return sender->rcvMsg(":server 461	ERR_NEEDMOREPARAMS");
		
// 			letter = 1;
// 		if (str[letter] == i){

// 		}
// 		else if (str[letter] == t){
			
// 		}
// 		else if (str[letter] == k){
			
// 		}
// 		else if (str[letter] == o){

// 		}
// 		else(str[letter] == l){

// 		}
// 		head++;	
// 	}
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
	if (rq[2].empty())
		Chan->setTopic(rq[MSG], sender);
	else
		Chan->setTopic(rq[2], sender);
}