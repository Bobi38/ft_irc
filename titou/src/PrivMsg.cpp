#include "PrivMsg.hpp"

std::string* split(char sep, std::string& str);

PrivMsg::PrivMsg(std::string msg)
    : ACmd(PRIVMSG, Prefix(msg), split(' ', msg)) {}

void PrivMsg::action(){
    std::cout << _tab[1] << " privmsg action" << std::endl;
}

void PrivMsg::error(){
    std::cout << _tab[0] << " privmsg error" << std::endl;
}

PrivMsg::~PrivMsg(){}