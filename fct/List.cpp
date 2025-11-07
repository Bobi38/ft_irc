#include "Maker.hpp"
#include "Channel.hpp"

void exec_list(Request& rq, Server* server, Client* client){
	std::cout << "1" << std::endl;
	(void)rq;
	std::string msg;
	client->rcvMsg(":server 321 " + client->getNick() + " Channel :Users Name");
	for (size_t i = 0; i < server->sizeChan(); ++i) {
		Channel* chan = server->getSChan(i);
		std::ostringstream oss;
		oss << chan->getNbMemb();
		std::string str = oss.str();
		std::cout << chan->getNbMemb() << std::endl;
		msg = ":server 322 " + client->getNick() + " " + chan->getName() + " " + str + " :" + chan->getTopic();
		client->rcvMsg(msg);
	}
	std::cout << "2" << std::endl;
	msg = ":server 323 " + client->getNick() + " :End of /LIST";
	client->rcvMsg(msg);
}