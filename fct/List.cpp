#include "Makerj.hpp"
#include "Channel.hpp"

void exec_list(Request& rq, Server* server, Client* client){
    if (client->getco() == false)
        return ;
    (void)rq;
    std::string msg;
    for (size_t i = 0; i < server->sizeChan(); ++i) {
        Channel* chan = server->getSChan(i);
        std::ostringstream oss;
        oss << chan->getNbMemb();
        std::string str = oss.str();
        msg = "322 " + client->getNick() + " " + chan->getName() + " " + str + " :" + chan->getTopic();
        client->rcvMsg(msg);
    }
    msg = "323 " + client->getNick() + " :End of /LIST";
    client->rcvMsg(msg);
}