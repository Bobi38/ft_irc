#include "topic.hpp"

topic::topic(const Request& rq): Request(rq){
}

topic::topic(const topic& other): Request(other){}

topic& topic::operator=(const topic& other){
	(void) other;
	return *this;
}

topic::~topic() {}

bool topic::check() const{
	return true;
}

void topic::exec() const{
	std::cout << "je suis un topic" << std::endl;  
}

Request* topic::newRequest(const Request& rq){
	return new topic(rq);
}