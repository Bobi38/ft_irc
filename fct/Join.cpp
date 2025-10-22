#include "Makerj.hpp"

bool init_chan_key(Request& rq,  std::vector<std::string>& chan, std::vector<std::string>& key){ 
    if (rq.size_tab() < 2 || rq.size_tab() > 3){
        return false;
    }
 
    std::stringstream ss_chan(rq[1]);
    std::string item;
    while (std::getline(ss_chan, item, ',')) {
        chan.push_back(item);
    }
   
    if (!rq[2].empty()) {
        std::stringstream ss_key(rq[2]);
        while (std::getline(ss_key, item, ',')) {
            key.push_back(item);
        }
    }
    while (key.size() < chan.size()) {
        key.push_back("");
    }
        return true;
}

bool init_chan(Server* server, Channel* chan, std::string psswd, Client* clt){
    if (clt->nbChan() >= 10){
        clt->rcvMsg("405 " +chan->getName() + " :You have joined too many channels");
        return false;  
    }
    if (chan->getNbMemb() >= 10){
        clt->rcvMsg("471 " +chan->getName() + " :Cannot join channel (+l)");
        return false;
    }
    if (chan->getStatutClt(clt) == PRESENT)
        return false; // faut il code erreur ???
    if (chan->getStatutClt(clt) == BAN && chan->get_b() == true){
        clt->rcvMsg("474 " +chan->getName() + " :Cannot join channel (+b)");
        return false;
    }
    if (chan->get_i() == true && (chan->getStatutClt(clt) != INVITE)){
        clt->rcvMsg("473 " +chan->getName() + " :Cannot join channel (+i)");
        return false;
    }
    if (!chan->getPssd().empty() && (psswd != chan->getPssd())){
        clt->rcvMsg("475 " +chan->getName() + " :Cannot join channel (+k)");
        return false;
    }
    server->linkClienttoChannel(clt, chan);
    return true;
}

void exec_join(Request& rq, Server* server, Client* client){
    if (client->getco() == false)
        return ;
    std::vector<std::string> chan;
    std::vector<std::string> key;
    Channel *TChan;

    if (init_chan_key(rq, chan, key) == false){
        client->rcvMsg("461 USER :Not enough parameters\r\n");
        return;
    }

    for(size_t i = 0; i < chan.size(); i++){
        if (chan[i][0] != '#' && chan[i][0] != '&'){
            client->rcvMsg("403 " + chan[i] + " :No such channel");
            continue;
        }
        TChan = server->find_channel(chan[i]);
        if (!TChan && chan[i] != ""){
            server->addChannel(chan[i], client);
            TChan = server->find_channel(chan[i]);
            server->linkClienttoChannel(client, TChan);
            if (key[i] != "")
                TChan->init_psswd(key[i]);
        }
        else
            if (init_chan(server, TChan, key[i], client) == false)
                continue ;
        client->rcvMsg(client->getMe() + " JOIN " + chan[i] );
        
    }
    TChan->print_all_clt();
    client->print_all_chan();
}