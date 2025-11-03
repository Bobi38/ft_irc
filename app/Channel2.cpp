#include "Channel.hpp"
#include "Request.hpp"

bool Channel::setTopic(std::string topic, Client* user){
	if (_mode[TOPIC - MOINS] == true && getStatutClt(user) != CHANOP){
		user->rcvMsg(":server 482 : " + getName() + " You're not channel operator");
		return false;
	}
	if (topic == Request::EMPTY_MSG)
		_topic = "";
	else
		_topic = topic;
	_topic_exist = true;
	return true;
}

std::string Channel::getTopic(){
	return _topic;
}

void	Channel::invit(Client* User, Client* Invit){
	int statut = getStatutClt(User);
	if (statut != CHANOP)
		return User->rcvMsg(":server 482 " + _name + " :You're not channel operator");//(443 -> ERR_USERONCHANNEL)":server 443 " + _name + " :out of channel"
	statut = getStatutClt(Invit);
	std::cout << "status " << statut << " " << Invit->getNick() << std::endl;
	if (statut == PRESENT || statut == CHANOP)
		return User->rcvMsg(":server 443 " + _name + " :is already on channel");
	
	addClient(Invit, INVITE);
	chan_msg(User->getMe() + " INVITE " + Invit->getName() + " " + _name);
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
	if (is_in(sender->getNick())==false)
		return sender->rcvMsg(":server 442 " + sender->getNick() +  _name + " :You're not on that channel");
	for(cci it = _member.begin(); it != _member.end(); it++){
		if (sender != it->second && (it->first == PRESENT || it->first == CHANOP))
			it->second->rcvMsg(sender->getMe() + " PRIVMSG " + _name + " :" + msg);
	}
}

void Channel::chan_msg(const std::string& msg){
	for(cci it = _member.begin(); it != _member.end(); it++){
		std::cout << _name << " " << it->second->getMe() << std::endl;
		if (it->first == PRESENT || it->first == CHANOP)
			it->second->rcvMsg(msg);
	}
}