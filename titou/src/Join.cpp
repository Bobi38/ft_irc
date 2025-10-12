#include "Join.hpp"

std::string* split(char sep, std::string& str);

Join::Join(std::string msg)
    : ACmd(JOIN, Prefix(msg), split(' ', msg)) {}

void Join::action(){
    std::cout << _tab[1] << " Join action" << std::endl;
}

void Join::error(){
    std::cout << _tab[0] << " Join error" << std::endl;
}

Join::~Join(){}

