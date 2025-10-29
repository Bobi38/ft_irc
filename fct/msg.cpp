#include "Makerj.hpp"
#include "Channel.hpp"
#include <vector>

void invit(Request& rq, Server* server, Client* sender){
	std::string user = rq[1];
	std::string chan = rq[2];

	if (user.empty() || chan.empty() || !rq[3].empty())
		return sender->rcvMsg(":server 461 " + rq[CMD] + "  :Not enough parameters");

	Client* User =  server->find_client(user);
	if (!User)
		return sender->rcvMsg(":server 401 " + user + " :No such nick/channel");
	Channel* Chan = server->find_channel(chan);
	if (!Chan)
		return sender->rcvMsg(":server 403 :" + chan + " :No such channel");

	Chan->invit(sender, User);
}

void prvmsg(Request& rq, Server* server, Client* sender){
	if (rq[1].empty())
		return sender->rcvMsg(":server 461 " + rq[CMD] + "  :Not enough parameters");

	for (int i = 1; !rq[i].empty(); i++){
		std::string dest = rq[i];
		if (dest[0] == '#'|| dest[0] == '&'){
			Channel* Chan = server->find_channel(dest);
			if (!Chan)
				sender->rcvMsg(":server 403 :" + dest + " :No such channel"); //(403 : ERRNOSUCHCHANNEL)
			else
				Chan->chan_msg(rq.getMsg(), sender, Chan);
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
		return sender->rcvMsg(":server 461 " + rq[CMD] + "  :Not enough parameters");

	Channel* Chan= server->find_channel(chan);
	if (!Chan)
		return sender->rcvMsg(":server 403 :" + chan + " :No such channel");

	if (rq[MSG].empty() && rq[2].empty()){
		if (Chan->getMODE(TOPIC_EXIST) == false)
			return sender->rcvMsg(":server 331 " + chan + " No topic is set");
		else
			return sender->rcvMsg(":server 332 " + chan + " :" + Chan->getTopic());
	}	

	if (rq[2].empty())
		Chan->setTopic(rq[MSG], sender);
	else
		Chan->setTopic(rq[2], sender);

}

void Channel::whoExec(Client* Client){
	std::string nickClient = Client->getNick();
	for (cci it = _member.begin(); it != _member.end(); it++){
		Client->rcvMsg(":server_irc 352 " \
					+ nickClient + " "\
					+ _name + " ~"\
					+ it->second->getName() \
					+ " 127.0.0.1 server_irc "\
					+ it->second->getNick() \
					+ " H" + (it->first == CHANOP ? "@" : "") \
					+ " :0");
	}
	Client->rcvMsg(":server 315 :" + nickClient + " " + _name + " :End of WHO list");
}

void who(Request& rq, Server* server, Client* sender){
	// std::cout << "\t\tWHO" << std::endl;
	std::string chan = rq[1];
	if (chan.empty())
		return sender->rcvMsg(":server 403 :" + chan + " :No such channel");
	// std::cout << "first test on WHO" << std::endl;
	Channel* Chan= server->find_channel(chan);
	if (!Chan)
		sender->rcvMsg(":server 315 " + chan + " :End of WHO list"); //(403 : ERRNOSUCHCHANNEL) juste pour WHO
	Chan->whoExec(sender);
}