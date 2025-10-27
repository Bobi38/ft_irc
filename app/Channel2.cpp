#include "Channel.hpp"
#include "Request.hpp"

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

std::string Channel::getTopic(){
	return _topic;
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
	// std::cout << "gros	lllllloooossssseeeeeerrrr   !!!!!!";
	for(cci it = _member.begin(); it != _member.end(); it++){
		// std::cout << it->second->getName();
		if (it->first == PRESENT || it->first == CHANOP)
			it->second->rcvMsg(msg);
	}
}