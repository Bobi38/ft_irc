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

void Channel::addClient(Client* client, int statut){
	bool is = true;
	if (!client->is_Channel(client->getName())){
		std::pair<int , Client*> tt (statut, client);
		_member.push_back(tt);
		is = false;
		return ;
	}
	for(cci it = _member.begin(); it != _member.end(); it++)
		if (it->second == client && it->first != BAN){
			it->first = statut;
			return ;
		}
	if (!is)
		chan_msg(client->getMe() + " JOIN " + _name);
}

bool Channel::get_i(){
	return _i_invonly;
}

bool Channel::get_b(){
	return _b_ban;
}

// int Channel::getStatutClt(Client* clt){
// 	if (!clt)
// 		return -1;
// 	std::cout << "cic\n" << _member.size() << " ici\n";
// 	cci iti = _member.begin();
// 	std::cout << "cic\n";
// 	cci itij = _member.end();
// 	iti = itij;
// 	for(cci it = _member.begin(); it != _member.end(); it++){
// 		if (it->second == clt){
// 			return it->first;
// 		}
// 	}
// 	return -1;
// }



int Channel::getStatutClt(Client* clt){

	// std::cout << "Debut Channel::getStatutClt " << std::endl;
	if (!clt) {
		// std::cout << "Client NULL!" << std::endl;
		return NO_PRESENT;
	}
	
	// std::cout << "Taille de _member: " << _member.size() << std::endl;
	// std::cout << "Recherche du client: " << clt->getName() << std::endl;
	
	for(cci it = _member.begin(); it != _member.end(); it++){
		// std::cout << "Comparaison avec: " << it->second->getName() << std::endl;
		if (it->second == clt){
			// std::cout << "Client trouvé! Statut: " << it->first << std::endl;
			return it->first;
		}
	}
	
	// std::cout << "Client non trouvé dans le canal!" << std::endl;
	return NO_PRESENT;
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
			return chan_msg(client->getMe() + " PART " + _name);
		}
	}
}

void Channel::chan_msg(const std::string& msg, Client* sender){
	// print_all_clt();
	if (!is_in(sender->getName()))
		return sender->rcvMsg(":server 442 " + _name + " :You're not on that channel" ); //(442 -> ERR_NOTONCHANNEL)"<channel> :You're not on that channel"
	for(cci it = _member.begin(); it != _member.end(); it++){
		// std::cout << "check :" << it->second->getNick() << " status " << it->first <<std::endl;
		if (it->second != sender && (it->first == PRESENT || it->first == CHANOP))
			it->second->rcvMsg(msg, sender);
	}
}

void Channel::chan_msg(const std::string& msg){
	// print_all_clt();
	for(cci it = _member.begin(); it != _member.end(); it++){
		// std::cout << "check :" << it->second->getNick() << " status " << it->first <<std::endl;
		if (it->first == PRESENT || it->first == CHANOP)
			it->second->rcvMsg(msg);
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

bool Channel::getMODE(int mod) const{
	return _mode[mod - MOINS];
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
	if (!is_in(user->getName()))
		return user->rcvMsg(":server 442 " + _name + " :You're not on that channel" ); //(442 -> ERR_NOTONCHANNEL)"<channel> :You're not on that channel"
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
	// std::cout << " intvit 1 " << User->getNick() << std::endl;

	int statut = getStatutClt(User);
	// std::cout << " intvit 2 " << User->getNick() << std::endl;
	
	if (statut > CHANOP)
		return User->rcvMsg(":server 443 " + _name + " :out of channel");//(443 -> ERR_USERONCHANNEL)
	// std::cout << " intvit 4 " << Invit->getNick() << std::endl;
	
	statut = getStatutClt(Invit);
	if (statut != NO_PRESENT)
		return User->rcvMsg(":server 443 " + _name + " :no invit" );//(443 -> ERR_USERONCHANNEL)
	// std::cout << " intvit 3 " << Invit->getNick() << std::endl;
	
	addClient(Invit, INVITE);
	// std::cout << " intvit 5 " << Invit->getNick() << std::endl;
	
	Invit->rcvMsg(User->getMe() + " INVITE " + Invit->getNick() + " :" + _name);
	// std::cout << " intvit 6 " << Invit->getNick() << std::endl;
}

void Channel::setMODE(int mode, std::string arg, Client* user){
	int status = getStatutClt(user);
	if (status == NO_PRESENT)
		return user->rcvMsg(":server 442 " + _name + " :You're not on that channel" ); // ok(442 -> ERR_NOTONCHANNEL)"<channel> :You're not on that channel"
	if (status != CHANOP)
		return user->rcvMsg(":server 482 " + _name + " :You're not channel operator" ); //ok 482
	bool set = mode > 0;
	bool old_mod = getMODE(mode);
	// mode = mode - MOINS;
	if (mode == OPERATOR){ // a gerer separement
		Client* clt = return_client(arg);
		if (!clt)
			return user->rcvMsg(":server 301 :no " + arg); //NOSUCHCLIENT
		status = getStatutClt(user);
		if (status == NO_PRESENT)
			return user->rcvMsg(":server 401 " + arg + " :No such nick/channel" );
		if (set && status == CHANOP)
			return change_statut(clt, CHANOP);
		return change_statut(clt, PRESENT);
	}
	if ((set == false && old_mod == false) || (set == true && old_mod == true))
		return putMode(user); // pas de changement de mode
	

	user->rcvMsg("MODE " + _name + (status ? " +" : " -") + "-+itklo"[mode]);
}

void Channel::putMode(Client* c){
	(void) c;
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
