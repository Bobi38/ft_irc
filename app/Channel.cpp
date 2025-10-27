#include "./include/Channel.hpp"
#include "Request.hpp"

std::pair<int,Client*> Channel::getPairC(size_t i){
	if (i >= _member.size())
		return std::pair<int,Client*>(0, NULL);
	return _member[i];
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
		if (it->second->getNick() == _client_name)
			return true;
	}
	return false;
}

void Channel::addClient(Client* client, int statut){
	bool is = true;
	if (!client->is_Channel(client->getName())){
		std::pair<int , Client*> tt (statut, client);
		_member.push_back(tt);
		is = false;
	}
	else
		for(cci it = _member.begin(); it != _member.end(); it++)
			if (it->second == client && it->first != BAN)
				it->first = statut;
	if (is == false)
		chan_msg(client->getMe() + " JOIN " + _name);
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

void Channel::init_psswd(std::string psswd){
	_psswrd = psswd;
}

Channel::~Channel(){
	_member.clear();
}

void Channel::new_op(std::string clt, Client* sender, int flag){
	Client* cc;
	cc = return_client(clt);
	if (getStatutClt(sender) != CHANOP) 
		return sender->rcvMsg(":server 482 " + _name + " :You're not channel operator");
	if (!cc)
		return sender->rcvMsg(":server 401 " + sender->getNick() + " " + clt + " :No such nick/channel");
	if (flag == PLUS)
		return change_statut(cc, CHANOP);
	return change_statut(cc, PRESENT);
}

void Channel::init_limit(std::string limit){
	for(size_t i = 0; i < limit.size(); i++){
		if (!isdigit(limit[i]))
			return ;
	}
	int lim = atoi(limit.c_str());
	_limit = lim;
	return ;	
}

bool Channel::setMOD(int mod, Client* user){
       if (getStatutClt(user) != CHANOP){ 
               user->rcvMsg(":server 482 " + _name + " :You're not channel operator");
               return false;
       }
       bool set = mod > 0;
       if (mod < 0)
               mod = -mod;
       if (set == _mode[LIMIT - MOINS])
               return true;
       _mode[mod - MOINS] = !_mode[mod - MOINS];
       return true;
}
