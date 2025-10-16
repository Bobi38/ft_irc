#include "include/Makerj.hpp"

void Maker::select(const std::string& str, Server* server, Client* client){
	bool second = client == _wClt;
	
	int size = str.size();
	if (!size)
		return ; // pas sur que ca arrive
	if (size == 1 || (size < 2 && str[size - 2] != '\r' && str[size - 1] != '\n')){
		_buff = (second ? _buff + str : str);
		_wClt = client;
		return ; // ne rien faire - en attente suite
	}
	std::string temp = str;
	temp.resize(size - 2);
	if (second)
		temp = _buff + temp;


	Request rq(temp, client); // client est inutile il faur le virer de request

	std::cout << "creation request avec cmd =" << rq.getCmd() << std::endl;
	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first)
			return table[i].second(&rq, server, client);
	}
}


void test2(Request* rq, Server* server, Client* client){
	(void) rq;
	(void) client;
	std::cout << "test avec INVITE " << server->check_psswd(5) << std::endl;
}

void test3(Request* rq, Server* server, Client* client){
	(void) server;
	std::cout << "test avec MODE" << client->getName() << std::endl;
	send(client->getFd(), rq->getMsg().c_str(), rq->getMsg().size(), 0);
}