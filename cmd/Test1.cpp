#include "include/Test1.hpp"

Test1::Test1(const Request& rq): Request(rq){
}

Test1::Test1(const Test1& other): Request(other){}

Test1& Test1::operator=(const Test1& other){
	(void) other;
	return *this;
}

Test1::~Test1() {}

bool Test1::check(const Server* serv) const{
	(void) serv;
	return true;
}

void Test1::exec(Server* serv){
	(void) serv;

	std::cout << "je suis un " << _tab[0] << std::endl;
	for (int i = 1; i < _tabSize; i++)
		std::cout << "je vois " << i << " :" << _tab[i] << "<---" << std::endl;
	if (!_msg.empty())
		std::cout << "mon message est :"<< _msg << "<---" << std::endl;
	std::cout << "si User :"<< _Clt.getName() << "<---" << std::endl;
}

Request* Test1::newTest1(const Request& rq){
	return new Test1(rq);
}