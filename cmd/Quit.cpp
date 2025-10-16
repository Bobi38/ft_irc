#include "include/Quit.hpp"

Join::Join(const Request& rq): Request(rq){
}

Join::Join(const Join& other): Request(other){}

Join& Join::operator=(const Join& other){
	(void) other;
	return *this;
}

Join::~Join() {}

bool Quit::check(const Server* serv, const Client* clt) const{
	(void) serv;
	(void) clt;
	return true;
}

void Quit::fd_send(Client* clt, std::set<int>& list){
	for(size_t i = 0; clt->getChan(i); i++){
		Channel* chan = clt->getChan(i);
		for(size_t y = 0;chan->getClient(y); y++){
			int testfd = chan->getClient(y)->getfd();
			if (clt->getfd() != testfd)
				list.push_back(testfd);
		}
	}
}

void Quit::send_all(Client* clt){
	std::set<int> list;
	fd_send(clt, list);
	for(size_t i = 0; i < list.size(); i++)
		send_msg(list[i], rq->message);
}

void Pass::exec(Server* serv, Client* clt){
	if (!clt)
		return;
	if (rq->message != "")
		send_all(clt);
	serv->dlt_client(clt, clt->getfd());
}

Request* Quit::newQuit(const Request& rq){
	return new Quit(rq);
}
