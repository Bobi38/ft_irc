#include "Bot.hpp"

Bot::Bot(){
    _nick = "bot";
    _name = "bot";
    _co = true;
    _psswd = true;
}

void Bot::rmClient(Client* clt){
    for(sco::iterator it = _score.begin(); it != _score.end(); it++){
        if (*it.first == clt)
            return _score.erase(it);
    }
}

void Bot::addClient(Client* clt){
    _score[clt] = std::make_pair(0, 0);
}

void Bot::getScore(Client *clt){
    std::ostringstream msg;
    msg << getMe() << " PRVMSG : il y a " << it->second.first << " à " << it->second.second;
    clt->rcvMsg(msg.str());
}

void Bot::addPoint(int result, Client* clt){
    if (result == LOSE)
        _score[clt].second += 1;
    if (result == W;IN)
        _score[clt]first += 1;
}