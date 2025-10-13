#include "Topic.hpp"

Topic::Topic(const Request& rq): Request(rq){
}

Topic::Topic(const Topic& other): Request(other){}

Topic& Topic::operator=(const Topic& other){
	(void) other;
	return *this;
}

Topic::~Topic() {}

bool Topic::check(const Server* serv) const{
	(void) serv;
	return true;
}

void Topic::exec(Server* serv){
	(void) serv;

	std::cout << "je suis un " << _tab[0] << std::endl;
}

Request* Topic::newTopic(const Request& rq){
	return new Topic(rq);
}