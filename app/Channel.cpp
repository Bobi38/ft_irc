#include "./include/Channel.hpp"
#include "Request.hpp"

std::pair<int,Client*> Channel::getPairC(size_t i){
	if (i >= _member.size())
		return std::pair<int,Client*>(0, NULL);
	return _member[i];
}

Client* Channel::return_client(std::string _client_name){
	std::cout << "here" << _client_name << std::endl;
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		std::cout << "in" << it->second->getNick() << std::endl;
		if (it->second->getNick() == _client_name)
			return it->second;
	}
	return NULL;
}

void Channel::change_statut(Client* clt, int new_st){

	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second->getNick() == clt->getNick()){
			it->first = new_st;
			return;
		}
	}
}

bool Channel::is_in(std::string _client_name){
	for(std::vector<std::pair<int,Client*> >::iterator it = _member.begin(); it != _member.end(); it++){
		if (it->second->getNick() == _client_name)
			return true;
	}
	return false;
}

void Channel::initt_psswd(std::string psd){
	_psswrd = psd;
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
			if (it->second == client)
				it->first = statut;
	if (statut == INVITE)
		return ;
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


Channel::~Channel(){
	_member.clear();
}

void Channel::new_op(std::vector<std::string>::iterator& z, Client* sender, int flag){
	Client* cc;
	cc = return_client(z->c_str());
	if (!cc)
		return sender->rcvMsg(":server 401 " + sender->getNick() + " " + z->c_str() + " :No such nick/channel");
	std::string s = (flag == -1) ? "-" : "+";
	chan_msg(sender->getMe() + " MODE " + _name + " " + s + "o "+ cc->getNick(), sender, this);
	if (flag == PLUS){
		change_statut(cc, CHANOP);
		z++;
		return ;
	}
	change_statut(cc, PRESENT);
	z++;
}

void Channel::new_ban(std::vector<std::string>::iterator& z, Client* sender, int flag){
	Client* cc;
	cc = return_client(z->c_str());
	if (!cc)
		return sender->rcvMsg(":server 401 " + sender->getNick() + " " + z->c_str() + " :No such nick/channel");
	std::string s = (flag == -1) ? "-" : "+";
	chan_msg(sender->getMe() + " MODE " + _name + " " + s + "b "+ cc->getNick(), sender, this);
	if (flag == +1){
		cc->rmChannel(this);
		change_statut(cc, BAN);
		z++;
		return;
	}
	rmClient(cc);
	z++;
}


bool Channel::setMOD(int mod, Client* user){
       if (getStatutClt(user) != CHANOP){ 
               user->rcvMsg(":server 482 " + user->getNick() + " :You're not channel operator");
               return false;
       }
       bool set = mod > 0;
	//    if (set == false)
	//    		std::cout << "set false " << mod << std::endl;
	// 	else
	//    		std::cout << "set true " << mod << std::endl;
       if (mod < 0)
               mod = -mod;
       if (set == _mode[mod - MOINS])
               return true;
       _mode[mod - MOINS] = set;
	//    if (_mode[mod - MOINS] == false)
	//    		std::cout << "mod false " << mod << std::endl;
	// 	else
	//    		std::cout << "mod true " << mod << std::endl;
       return true;
}
