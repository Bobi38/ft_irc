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

void Bot::getScore(Client *clt){
    sco::iterator it = _score.begin();
    for(; it != _score.end(); it++){
        if (it->first == clt)
            break;
    }
    std::ostringstream msg;
    msg << getMe() << " PRVMSG : il y a " << it->second.first << " à " << it->second.second;
    clt->rcvMsg(msg.str());
}

void Bot::addPoint(int result, Client* clt, Channel* Chan){
    if (result == LOSE){
        _score[clt].second += 1;
        clt->rcvMsg("Desole tu as perdu gros nul");
        Chan->chan_msgg(clt->getNick() + " a perdu a pile ou face", this, Chan, clt);
    }
    if (result == WIN){
        _score[clt].first += 1;
        clt->rcvMsg("Bon tu as gagne ... mais tu n'y arrivera plus");
        Chan->chan_msgg(clt->getNick() + " a gagne a pile ou face", this, Chan, clt);
    }
}