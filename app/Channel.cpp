#include "./include/Channel.hpp"
#include "Request.hpp"

Channel::Channel(std::string name, Client* client): _name(name), _limit(-1), _i_invonly(false), _b_ban(false), _t_topicop(false), _topic_exist(false) {
	if (client){
		std::pair<int , Client*> tt (CHANOP, client);
		_member.push_back(tt);
	}
}

std::string Channel::getName(){
	return _name;
}

size_t Channel::getNbMemb(){
	return _member.size();
}

Client* Channel::getClient(size_t i){
	if (i >= _member.size())
		return NULL;
	return _member[i].second;
}

Client* Channel::return_client(std::string _client_name){
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second->getName() == _client_name)
			return it->second;
	}
	return NULL;
}

void Channel::change_statut(Client* clt, int new_st){
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second == clt)
			it->first = new_st;
	}
}

bool Channel::is_in(std::string _client_name){
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second->getName() == _client_name)
			return true;
	}
	return false;
}

void Channel::addClient(Client* client){
	if (!client->is_Channel(client->getName())){
		std::pair<int , Client*> tt (PRESENT, client);
		_member.push_back(tt);
	}
	else {
		for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
			if (it->second == client && it->first != BAN)
				it->first = PRESENT;
		}
	}
}

bool Channel::get_i(){
	return _i_invonly;
}

bool Channel::get_b(){
	return _b_ban;
}

int Channel::getStatutClt(Client* clt){
	if (!clt)
		return -1;
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second == clt){
			return it->first;
		}
	}
	return -1;
}

std::string Channel::getPssd(){
	return _psswrd;
}

void Channel::rmClient(Client* client){
	if (!client)
		return ;
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second == client){
			_member.erase(it);
			break;
		}
	}
}

void Channel::chan_msg(const std::string& msg, Client* sender){
	for(cci it = _member.begin(); it != _member.end(); it++){
		if (it->first == PRESENT || it->first == CHANOP)
			return it->second->rcvMsg(msg, sender);
	}
}

void Channel::init_psswd(std::string psswd){
	if (psswd == "")
		return ;
	_psswrd = psswd;
	if (!_i_invonly) // je crois qu on peux faire sauter cette ligne
		_i_invonly = true;
}

bool Channel::getMOD(int mod) const{ //fct a verifier
	(void) _t_topicop;
	(void) _topic_exist;
	(void) _limit; //a supprimer
	return *(&_i_invonly + (mod - PRIVATE));
}


std::string Channel::getTopic()const{
	return _topic;
}

void Channel::setMOD(int mod, Client* user){ //fct a verifier
	if (getStatutClt(user) != CHANOP)
		return user->rcvMsg(":server 482 " + _name + " :only CHANOP");
	bool set = mod > 0;
	if (mod < 0)
		mod = -mod;
	*(&_i_invonly + (mod - PRIVATE)) = set;
}

void Channel::setTopic(std::string topic, Client* user){
	if (_t_topicop && getStatutClt(user) != CHANOP)
		return user->rcvMsg(":server 482 " + _name + " :only CHANOP");
	if (topic == Request::EMPTY_MSG)
		_topic = "";
	else
		_topic = topic;
	_topic_exist = true;

	chan_msg("TOPIC " + _name + " :" + _topic, user);
}

Channel::~Channel(){
	_member.clear();
}

void Channel::print_all_clt(){
	std::cout << getName() << " ";
    for(size_t i = 0; i < _member.size(); i++){
		std::cout << _member[i].second->getName() << " - " << _member[i].first << " // ";
	}
	std::cout << std::endl;
}
