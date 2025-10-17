#include "Makerj.hpp"
#include "Channel.hpp"

void msgprv(Request& rq, Server* server, Client* sender){
	std::cout << rq[1] << std::endl;
	if (rq[1].empty())
		return sender->rcvMsg(":server 301 "); // attention retour
	std::cout << "first check" << std::endl;
	for (int i = 1; !rq[i].empty(); i++){
		std::string dest = rq[i];
		if (dest[0] == '#'|| dest[0] == '&'){
			Channel* Chan = server->find_channel(dest);
			Chan->chan_msg(rq.getMsg(), sender);
			return ;
		}
		else {
			Client* clrcv = server->find_client(dest);
			std::cout << clrcv->getName() << " nick  :" << clrcv->getNick() << std::endl; // pas recu le name
			clrcv->rcvMsg(rq.getMsg(), sender);
		}
	}
}