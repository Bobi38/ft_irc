#include "Channel.hpp"

Channel::Channel(std::string name, Client* client): _name(name), _limit(-1), _topic_exist(false) {
	if (client){
		std::pair<int , Client*> tt (CHANOP, client);
		_member.push_back(tt);
	}
	for (int i = 0; i < 6; ++i)
		_mode[i] = false;
}

std::string Channel::getName(){
	return _name;
}

Client* Channel::getClient(size_t i){
	if (i >= _member.size())
		return NULL;
	return _member[i].second;
}

int Channel::getStatutClt(Client* clt){
	if (!clt)
		return -1;
	for(cci it = _member.begin(); it != _member.end(); it++){
		if (it->second == clt){
			return it->first;
		}
	}
	return -1;
}

std::string Channel::getPssd(){
	return _psswrd;
}

std::string Channel::str_mode = "-+itklo";

bool Channel::getMODE(int mod) const{
	// std::cout << "je renvoie " << mod <<" "<< (_mode[mod - MOINS] ? "TRUE" : "FALSE") << std::endl;
	return _mode[mod - MOINS];
}

void Channel::print_all_clt(){
	std::cout << getName() << " ";
	for(size_t i = 0; i < _member.size(); i++){
		std::cout << _member[i].second->getName() << " - " << _member[i].first << " // ";
	}
	std::cout << std::endl;
}

int Channel::getNbMemb(){
	int cpt = 0;
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->first == CHANOP || it->first == PRESENT){
			cpt++;
		}
	}
	return cpt;
}
