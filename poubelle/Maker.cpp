#include "Maker.hpp"

std::string* split(char sep, std::string& str);

Maker::Maker(){}

Maker::~Maker(){}

ACmd* Maker::makeJoin(std::string msg){
    return new Join(msg);
}

ACmd* Maker::makePrivMsg(std::string msg){
    return new PrivMsg(msg);
}

ACmd* Maker::makeCmd(int type, std::string msg){
    int list[] = {1, 2};
	ACmd* (Maker::*lev[])( std::string) ={&Maker::makeJoin, &Maker::makePrivMsg};

    for(int i = 0; i < 2; i++){
		if (list[i] == type){
            std::cout << "ici" << i << std::endl;
			return (this->*lev[i])(msg);
        }
	}
	std::cout << "error" << std::endl;
	return NULL;
}