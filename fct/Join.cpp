#include "Makerj.hpp"

bool init_chan_key(Request& rq,  std::vector<std::string>& chan, std::vector<std::string>& key){ 
    if (rq.size_tab() < 1 || rq.size_tab() > 2){
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

void init_chan(Server* server, Channel* chan, std::string psswd, Client* clt){
    if (chan->nb_user() >= 10){
        client->rcvMsg("471 " +TChan->getName() + " :Cannot join channel (+l)");
        return;
    }
    if (chan->getStatutClt(clt) == PRESENT)
        return; // faut il code erreur ???
    if (chan->getStatutClt(clt) == BAN && chan->get_b() == true){
        client->rcvMsg("474 " +TChan->getName() + " :Cannot join channel (+b)");
        return;
    }
    if (chan->get_i() == true && (chan->getStatutClt(clt) != INVITE)){
        client->rcvMsg("473 " +TChan->getName() + " :Cannot join channel (+i)");
        return;
    }
    if (!chan->getPssd().empty() && (psswd != chan->getPssd())){
        client->rcvMsg("475 " +TChan->getName() + " :Cannot join channel (+k)");
        return;
    }
    server->linkClienttoChannel(clt, chan);
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
            // send_msg_client_Chan(client->getfd(), "wrong name chan");
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
            init_chan(server, TChan, key[i], client);
        
    }
    TChan->print_all_clt();
    client->print_all_chan();
}