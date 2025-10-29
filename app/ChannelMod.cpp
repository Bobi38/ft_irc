#include "Channel.hpp"

void Channel::init_limit(int sign, Client* clt, std::vector<std::string>::iterator& z){
    if (setMOD(LIMIT * sign, clt) == false)
        return ;
    std::string s = (sign == -1) ? "-" : "+";
    if (sign == -1) {
        _limit = 0;
    chan_msg(clt->getMe() + " MODE " + _name + " " + s + "l", clt, this);
        return;
    }
    if (z->empty() || atoi(z->c_str()) <= 0)
        return clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters");
    std::string limit = z->c_str();
    for(size_t i = 0; i < (limit).size(); i++){
		if (!isdigit(limit[i]))
			return clt->rcvMsg("PASSWORD NOT VALID: " + limit);
	}
    _limit = atoi(limit.c_str());
    chan_msg(clt->getMe() + " MODE " + _name + " " + s + "l " + limit, clt, this);
    z++; 
}

void Channel::init_psswd(int sign, Client* clt, std::vector<std::string>::iterator& z){
    if (setMOD(KEY * sign, clt) == false)
        return ;
    std::string s = (sign == -1) ? "-" : "+";
    if (sign == -1) {
        _psswrd = "";
        chan_msg(clt->getMe() + " MODE " + _name + " " + s + "k", clt, this);
        return;
    }
    if (z->empty())
        return clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters");
    _psswrd = z->c_str();
    chan_msg(clt->getMe() + " MODE " + _name + " " + s + "k", clt, this);
    z++;
}

static std::string init_ban(Channel* chan){
	std::string namel;
	for(size_t i = 0; i < static_cast<size_t>(chan->getNbMemb()); i++){
		if (chan->getPairC(i).first == BAN)
			namel = namel + chan->getPairC(i).second->getNick() + " ";
	}
	namel.erase(namel.end() - 1);
	return namel;
}

void Channel::mod_ban(int sign, Client* clt, std::vector<std::string>::iterator& z){
    if (getStatutClt(clt) != CHANOP)
        return clt->rcvMsg(":server 482 " + clt->getNick() + " :You're not channel operator");
    if (z->empty() && sign == -1)
        return clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters");
    if (z->empty() && sign == +1){
        clt->rcvMsg(":server_irc 367 " + clt->getNick() + " = " + _name + " :" + init_ban(this));
        return clt->rcvMsg(":server_irc 368 " + clt->getNick() + " " + _name + " :End of /NAMES list");
    }
    new_ban(z, clt, sign);
}

void Channel::mod_op(int sign, Client* clt, std::vector<std::string>::iterator& z){
    if (getStatutClt(clt) != CHANOP)
        return clt->rcvMsg(":server 482 " + clt->getNick() + " :You're not channel operator");
    if (z->empty())
        return clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters");
    new_op(z, clt, sign);
}