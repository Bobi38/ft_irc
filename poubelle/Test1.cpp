#include "include/Test1.hpp"

Test1::Test1(const Request& rq): Request(rq), _flag(false){
}

Test1::Test1(const Test1& other): Request(other){}

Test1& Test1::operator=(const Test1& other){
	(void) other;
	return *this;
}

Test1::~Test1() {}

bool Test1::check(const Server* serv, const Client* clt) const{
	(void) serv;
	(void) clt;
	return true;
}

void Test1::exec(Server* serv, Client* clt){
	(void) serv;
	_flag = this->check(serv, clt);
	if (!_flag){
		std::cout << "bizarre ce false" << std::endl;
		return ;
	}
	std::cout << "je suis un " << _tab[0] << std::endl;
	for (int i = 1; i < _tabSize; i++)
		std::cout << "je vois " << i << " :" << _tab[i] << "<---" << std::endl;
	if (!_msg.empty())
		std::cout << "mon message est :"<< _msg << "<---" << std::endl;
	std::cout << "si User :"<< clt->getName() << "<---" << std::endl;
}

Request* Test1::newTest1(const Request& rq){
	return new Test1(rq);
}