#include "Makerj.hpp"

void msgprv(Request& rq, Server* server, Client* client){
	std::cout << rq[1] << std::endl;
	if (rq[1].empty())
		return client->rcvMsg(":server 301 "); // attention retour
	std::cout << "first check" << std::endl;
	for (int i = 1; !rq[i].empty(); i++){
		Client* clrcv = server->find_client(rq[1]);
		std::cout << clrcv->getName() << " nick  :" << clrcv->getNick() << std::endl;
		clrcv->rcvMsg(rq.getMsg(), client);
	}
}