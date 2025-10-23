#include "Makerj.hpp"
#include "Channel.hpp"


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
	
	Chan->invit(sender, User);
}

void msgprv(Request& rq, Server* server, Client* sender){
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
	std::string chan = rq[1];
	if (chan.empty())
		return sender->rcvMsg(":server 301 "); // attention retour
	
	Channel* Chan= server->find_channel(chan);
	if (!Chan)
		return sender->rcvMsg(":server 403 :no " + chan); //(403 : ERRNOSUCHCHANNEL)

	if (rq[MSG].empty() && rq[2].empty()){
		if (!Chan->getMOD(TOPIC_EXIST))
			return sender->rcvMsg(":server 331 " + chan + " No topic is set"); //(403 : ERRNOSUCHCHANNEL)
		else
			return sender->rcvMsg(":server 332 " + chan + " :" + Chan->getTopic());
	}	
	
	if (rq[2].empty())
		Chan->setTopic(rq[MSG], sender);
	else
		Chan->setTopic(rq[2], sender);
}