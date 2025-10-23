#include "Makerj.hpp"
#include "Channel.hpp"

bool init_chan(Request& rq,  std::vector<std::string>& chan){
    if (rq.size_tab() != 2){
        return false;
    }
    std::stringstream ss_chan(rq[1]);
    std::string item;
    while (std::getline(ss_chan, item, ',')) {
        if (item[0] != '#' && item[0] != '&')
            chan.push_back("");
        chan.push_back(item);
    }
    return true;
}

void exec_part(Request& rq, Server* server, Client* client){
    if (client->getco() == false)
        return ;
    if (rq.size_tab() < 3) {
        client->rcvMsg("461 USER :Not enough parameters");
        return;
    }
    std::vector<std::string> chan;
    Channel* TChan;

    if (init_chan(rq, chan) == false)
        return;
    for(size_t i = 0; i < chan.size(); i++){
        TChan = server->find_channel(chan[i]);
        if (!TChan){
            client->rcvMsg("403 " +TChan->getName() + " :No such channel");
            continue;
        }
        if (client->is_Channel(chan[i])){
            server->unlinkClienttoChannel(client, TChan);
        }
        else
            client->rcvMsg("442 " +TChan->getName() + " : You're not on that channel");
        TChan = NULL;
    }
}