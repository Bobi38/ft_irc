#include "Makerj.hpp"
#include "Channel.hpp"

void exec_list(Request& rq, Server* server, Client* client){
    (void)rq;
    std::string msg;
    for (size_t i = 0; i < server->sizeChan(); ++i) {
        Channel* chan = server->getSChan(i);
        msg = "322 " + client->getNick() + " " + chan->getName() + " " + " :" + chan->getTopic();
        send_msg(client->getfd(), msg);
    }
    msg = "323 " + client->getNick() + " :End of /LIST";
    send_msg(client->getfd(), msg);
}