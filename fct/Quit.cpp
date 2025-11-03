#include "Makerj.hpp"

void fd_send(Client* clt, std::set<int>& list, bool in){
	for(size_t i = 0; clt->getChan(i); i++){
		Channel* chan = clt->getChan(i);
		if (chan->is_inv(clt->getNick()))
			continue;
		for(size_t y = 0;chan->getClient(y); y++){
			int testfd = chan->getClient(y)->getfd();
			if (in == false && testfd != clt->getfd())
				list.insert(testfd);
		}
	}
}

void send_all_chan(std::string msg, Client* clt, Server* serv){
	std::set<int> list;
	fd_send(clt, list, true);
	for(std::set<int>::iterator it = list.begin(); it != list.end(); it++){
		Client *tmp;
		tmp = serv->find_fd(*it);
		tmp->rcvMsg(msg);
	}
}

void send_all(Request& rq, Client* clt){
	std::set<int> list;
	fd_send(clt, list, false);
	for(std::set<int>::iterator it = list.begin(); it != list.end(); it++)
		send_msg(*it, rq.getMsg());
}

void exec_quit(Request& rq, Server* serv, Client* clt){
	if (clt->getco() == false)
		return ;
	if (!clt)
		return;
	if (rq.getMsg() != Request::EMPTY_MSG)
		send_all(rq, clt);
	std::cout << "le fd a quit  " << clt->getfd()<<  std::endl;
	serv->dlt_client(clt, clt->getfd());
}