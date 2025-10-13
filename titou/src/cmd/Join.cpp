#include "Join.hpp"

Join::Join(const Request& rq): Request(rq){
}

Join::Join(const Join& other): Request(other){}

Join& Join::operator=(const Join& other){
	(void) other;
	return *this;
}

Join::~Join() {}

bool Join::check(const Server* serv) const{
	(void) serv;
	return true;
}

void Join::exec(Server* serv){
	(void) serv;

	std::cout << "je suis un " << _tab[0] << std::endl;  
}

Request* Join::newJoin(const Request& rq){
	return new Join(rq);
}
