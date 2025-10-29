#include "Makerj.hpp"

bool init_chan_key(Request& rq,  std::vector<std::string>& chan, std::vector<std::string>& key){ 
	if (rq.size_tab() < 2 || rq.size_tab() > 3){
		return false;
	}
 
	std::stringstream ss_chan(rq[1]);
	std::string item;
	while (std::getline(ss_chan, item, ','))
		chan.push_back(item);

	if (!rq[2].empty()) {
		std::stringstream ss_key(rq[2]);
		while (std::getline(ss_key, item, ','))
			key.push_back(item);
			
	}
	while (key.size() < chan.size())
		key.push_back("");

	return true;
}

Channel* init_chan(Server* server, std::string& chan, std::string psswd, Client* clt){
	if (chan[0] != '#' && chan[0] != '&'){
		clt->rcvMsg("403 " + chan + " :No such channel");
		return NULL;
	}

	Channel* pchan = server->find_channel(chan);
	if (!pchan){
		pchan = server->addChannel(chan, clt);
		if (!psswd.empty())
			pchan->initt_psswd(psswd);
		clt->rcvMsg(clt->getMe() + " JOIN " + chan);
		return pchan;
	}
	int statut = pchan->getStatutClt(clt);
	if (clt->nbChan() >= 10){
		clt->rcvMsg("405 " + pchan->getName() + " :You have joined too many channels");
	}
	else if (pchan->getNbMemb() >= 10){
		clt->rcvMsg("471 " + pchan->getName() + " :Cannot join channel (+l)");
	}
	else if (pchan->getStatutClt(clt) == PRESENT)
		return NULL;

	else if (statut == BAN && pchan->getMODE(NO_BAN) == true){
		clt->rcvMsg("474 " + pchan->getName() + " :Cannot join channel (+b)");
	}
	else if (pchan->getMODE(INVITE_ONLY) == true && (statut != INVITE)){
		clt->rcvMsg("473 " + pchan->getName() + " :Cannot join channel (+i)");
	}
	else if (pchan->getMODE(KEY) == true && (psswd != pchan->getPssd())){
		clt->rcvMsg("475 " + pchan->getName() + " :Cannot join channel (+k)");
	}
    else if (pchan->is_in(clt->getNick()) == true)
        return NULL;
	else{ 
		pchan->addClient(clt, PRESENT);
		return pchan;
	}
	return NULL;
}

std::string init_namel(Channel* chan){
	std::string namel;
	for(size_t i = 0; i < static_cast<size_t>(chan->getNbMemb()); i++){
		if (chan->getPairC(i).first == CHANOP)
			namel = namel + "@" + chan->getPairC(i).second->getNick() + " ";
		else if (chan->getPairC(i).first == PRESENT)
			namel = namel + chan->getPairC(i).second->getNick() + " ";
	}
	namel.erase(namel.end() - 1);
	return namel;
}

void exec_join(Request& rq, Server* server, Client* client){
	std::vector<std::string> chan;
	std::vector<std::string> key;

	if (init_chan_key(rq, chan, key) == false){
		client->rcvMsg("461 USER :Not enough parameters\r\n");
		return;
	}

	for(size_t i = 0; i < chan.size(); i++){
		if (chan[i][0] != '#' && chan[i][0] != '&'){
			client->rcvMsg("403 " + chan[i] + " :No such channel");
			continue;
		}
		Channel* TChan = init_chan(server, chan[i], key[i], client);
		if (!TChan)
			continue ;

		client->addChannel(TChan);
		if (TChan->getTopic() != "")
			client->rcvMsg(":server_irc 332 " + client->getNick() + " " + chan[i] + " :" + TChan->getTopic());
		
		client->rcvMsg(":server_irc 353 " + client->getNick() + " = " + chan[i] + " :" + init_namel(TChan));
		client->rcvMsg(":server_irc 366 " + client->getNick() + " " + chan[i] + " :End of /NAMES list");
	}
}
