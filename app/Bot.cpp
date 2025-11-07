#include "Bot.hpp"
#include <sstream>

Bot::Bot(){
    _nick = "bot";
    _name = "bot";
    _co = true;
    _psswd = true;
}

void Bot::rmClient(Client* clt){
    for(sco::iterator it = _score.begin(); it != _score.end(); it++){
        if (it->first == clt)
            return _score.erase(it);
    }
}

void Bot::addClient(Client* clt){
    _score[clt] = std::make_pair(0, 0);
}

void Bot::getScore(Client *clt, Channel* chan){
    sco::iterator it = _score.begin();
    for(; it != _score.end(); it++){
        if (it->first == clt)
            break;
    }
    std::ostringstream msg;
    msg << "Il y a " << it->second.first << " à " << it->second.second;
    std::ostringstream msg2;
    msg2 << "Le score de " << it->first->getNick() << " est de "  << it->second.first << " à " << it->second.second;
    if (chan != NULL)
        return chan->chan_msgg(msg2.str(), clt, msg.str(), this->getMe());
    clt->rcvMsg(msg.str(), this);
}

void Bot::addPoint(int result, Client* clt, Channel* Chan){
    if (result == LOSE){
        _score[clt].second += 1;
        if (Chan == NULL)
            clt->rcvMsg("Desole tu as perdu gros nul", this);
        if (Chan != NULL)
            Chan->chan_msgg(clt->getNick() + " a perdu a pile ou face", clt, "Desole tu as perdu gros nul", this->getMe());
    }
    if (result == WIN){
        _score[clt].first += 1;
        if (Chan == NULL)
            clt->rcvMsg("Bon tu as gagne ... mais tu n'y arrivera plus", this);
        if (Chan != NULL)
            Chan->chan_msgg(clt->getNick() + " a gagne a pile ou face", clt, "Bon tu as gagne ... mais tu n'y arrivera plus", this->getMe());
    }
}