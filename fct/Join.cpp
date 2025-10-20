#include "Makerj.hpp"

bool init_chan_key(Request& rq,  std::vector<std::string>& chan, std::vector<std::string>& key){
    if (rq.size_tab() < 1 || rq.size_tab() > 2){
        return false;
    }
    std::stringstream ss_chan(rq[1]);
    std::string item;
    while (std::getline(ss_chan, item, ',')) {
        if (item[0] != '#' && item[0] != '&')
            return false;
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
    if (chan->getStatutClt(clt) == PRESENT)
        return; // faut il code erreur ???
    if (chan->getStatutClt(clt) == BAN)
        return; // rajouter code erreur
    if (chan->get_i() == true && (chan->getStatutClt(clt) != INVITE))
        return ;
    if (!chan->getPssd().empty() && (psswd != chan->getPssd()))
        return ; // wrong code erreur
    server->linkClienttoChannel(clt, chan);
}

void exec_join(Request& rq, Server* server, Client* client){
    std::vector<std::string> chan;
    std::vector<std::string> key;
    Channel *TChan;

    init_chan_key(rq, chan, key);
    for(size_t i = 0; i < chan.size(); i++){
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
}