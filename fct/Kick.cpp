#include "Maker.hpp"
#include "Channel.hpp"

void exec_kick(Request& rq, Server* server, Client* client){
	if (client->getco() == false)
		return ;
	Channel* TChan;
	Client* TClt;

	TChan = server->find_channel(rq[1]);
	if (!TChan){
		client->rcvMsg("403 " + rq[1] + " :No such channel");
		return ;
	}
	TClt = TChan->return_client(rq[2]);
	if (!TClt || (TChan->getStatutClt(TClt) != PRESENT && TChan->getStatutClt(TClt) != CHANOP && TChan->getStatutClt(TClt) != BOT)){
		client->rcvMsg("442 " + rq[2] + " :You're not on that channel");
		return ;
	}
	if (TChan->is_in(client->getNick()) == false){
		client->rcvMsg("442 " + client->getNick() + " :You're not on that channel");
		return ;	   
	}
	if (TChan->getStatutClt(client) != CHANOP){
		client->rcvMsg("482 " + client->getNick() + " :You're not channel operator");
		return ;
	}
	TChan->chan_msg(client->getMe() + " KICK " + TChan->getName() + " " + TClt->getNick());
	TClt->rmChannel(TChan);
	TChan->change_statut(TClt, BAN);


}