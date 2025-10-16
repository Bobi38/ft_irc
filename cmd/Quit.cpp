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

void Pass::exec(Server* serv, Client* clt){
	if (!clt)
		return;
	if (rq->message != "")
	serv->dlt_client(clt, clt->getfd())
		send  
}

Request* Quit::newQuit(const Request& rq){
	return new Quit(rq);
}
