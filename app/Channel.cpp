#include "./include/Channel.hpp"
#include "Request.hpp"

Channel::Channel(std::string name, Client* client): _name(name), _limit(-1), _i_invonly(false), _b_ban(false), _t_topicop(false), _topic_exist(false) {
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

size_t Channel::getNbMemb(){
	return _member.size();
}

Client* Channel::getClient(size_t i){
	if (i >= _member.size())
		return NULL;
	return _member[i].second;
}

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
		if (it->second->getName() == _client_name)
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
		if (sender != it->second && (it->first == PRESENT || it->first == CHANOP))
			it->second->rcvMsg(msg, sender);
	}
}

void Channel::chan_msg(const std::string& msg, Client* sender, Channel* Chan){
	if (Chan != this)
		return ;
	for(cci it = _member.begin(); it != _member.end(); it++){
		if (sender != it->second && (it->first == PRESENT || it->first == CHANOP))
			it->second->rcvMsg(sender->getMe() + " PRIVMSG " + _name + " :" + msg);
	}
}

void Channel::chan_msg(const std::string& msg){
	// std::cout << "gros    lllllloooossssseeeeeerrrr   !!!!!!";
	for(cci it = _member.begin(); it != _member.end(); it++){
		// std::cout << it->second->getName();
		if (it->first == PRESENT || it->first == CHANOP)
			it->second->rcvMsg(msg);
	}
}

void Channel::init_psswd(std::string psswd){
	// if (psswd == "")
	// 	return ;
	_psswrd = psswd;
	// if (!_i_invonly) // je crois qu on peux faire sauter cette ligne
	// 	_i_invonly = true;
}

bool Channel::getMOD(int mod) const{ //fct a verifier
	(void) _t_topicop;
	(void) _topic_exist;
	(void) _limit; //a supprimer
	return *(&_i_invonly + (mod - PRIVATE));
}

std::string Channel::str_mode = "-+itklo";

bool Channel::getMODE(int mod) const{
	return _mode[mod - MOINS];
}

std::string Channel::getTopic()const{
	return _topic;
}

// void Channel::setMOD(int mod, Client* user){ //fct a verifier
// 	if (getStatutClt(user) != CHANOP)
// 		return user->rcvMsg(":server 482 " + _name + " :only CHANOP");
// 	bool set = mod > 0;
// 	if (mod < 0)
// 		mod = -mod;
// 	*(&_i_invonly + (mod - PRIVATE)) = set;
// }

bool Channel::setMOD(int mod, Client* user){
	if (getStatutClt(user) != CHANOP){ 
		user->rcvMsg(":server 482 " + _name + " :You're not channel operator");
		return false;
	}
	std::cout << "1" << std::endl;
	bool set = mod > 0;
	if (mod < 0)
		mod = -mod;
	std::cout << "2" << std::endl;
	if (set == _mode[LIMIT - MOINS])
		return true;
	std::cout << "3" << std::endl;
	_mode[mod - MOINS] = !_mode[mod - MOINS];
	std::cout << "4" << std::endl;
	return true;
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


void	Channel::invit(Client* User, Client* Invit){
	int statut = getStatutClt(User);
	if (statut != PRESENT && statut != CHANOP)
		return User->rcvMsg(":server 443 " + _name + " :out of channel");//(443 -> ERR_USERONCHANNEL)
	statut = getStatutClt(Invit);
	if (statut >= PRESENT && statut <= BAN)
		return User->rcvMsg(":server 443 " + _name + " :no invit" );//(443 -> ERR_USERONCHANNEL)
	
	addClient(Invit, INVITE);
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

void Channel::print_all_clt(){
	std::cout << getName() << " ";
    for(size_t i = 0; i < _member.size(); i++){
		std::cout << _member[i].second->getName() << " - " << _member[i].first << " // ";
	}
	std::cout << std::endl;
}

int Channel::getNbMemb() const{
	int cpt = 0;

	for(size_t i = 0; i < _member.size(); i++){
		if (_member[i].first == CHANOP ||  _member[i].first == PRESENT)
			cpt++;
	}
	return cpt;
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

std::string Channel::getTopic(){
	return _topic;
}