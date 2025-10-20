#include "Makerj.hpp"

bool init_chan_key(Request& rq,  std::vector<std::string>& chan, std::vector<std::string>& key){
    std::cout << "9" << std::endl;
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
    std::cout << "1" << std::endl;
    if (chan->getStatutClt(clt) == PRESENT)
        return; // faut il code erreur ???
    std::cout << "2" << std::endl;
    if (chan->getStatutClt(clt) == BAN && chan->get_b() == true)
        return; // rajouter code erreur
    std::cout << "3" << std::endl;
    if (chan->get_i() == true && (chan->getStatutClt(clt) != INVITE))
        return ;
    std::cout << "4" << std::endl;
    if (!chan->getPssd().empty() && (psswd != chan->getPssd()))
        return ; // wrong code erreur
    server->linkClienttoChannel(clt, chan);
}

void exec_join(Request& rq, Server* server, Client* client){
    std::cout << " je suis join" << std::endl;
    std::cout << " jclt = " << client->getName() << std::endl;
    std::vector<std::string> chan;
    std::vector<std::string> key;
    Channel *TChan;

    if (init_chan_key(rq, chan, key) == false)
        return ;
    std::cout << "10" << std::endl;

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
    TChan->print_all_clt();
    client->print_all_chan();
}