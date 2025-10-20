#include "Makerj.hpp"
#include "Channel.hpp"

void exec_kick(Request& rq, Server* server, Client* client){
    Channel* TChan;
    Client* TClt;

    TChan = server->find_channel(rq[1]);
    if (!TChan)
        return ;
    TClt = TChan->return_client(rq[2]);
    if (!TClt || TChan->is_in(client->getName()) == false)
        return ;
    if (TChan->getStatutClt(TClt) != PRESENT)
        return ;
    if (TChan->getStatutClt(client) != OPER)
        return ;
    TClt->rmChannel(TChan);
    TChan->change_statut(TClt, BAN);

}