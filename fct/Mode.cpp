#include "Makerj.hpp"
#include "Channel.hpp"

static void init_map(Request& rq,  std::vector<std::string> &flag){
    if (rq.size_tab() < 3)
        return ;
    for(int i = 2; i < rq.size_tab(); i++){
        std::string rr = rq[i];
        if (rr[0] != '-' && rr[0] != '+'){
            rr = '@' + rr;
            flag.push_back(rr);
            continue;
        }
        size_t pos = 0;
        while(pos < rr.size()){
            size_t start = pos;
            size_t end = rr.find_first_of("+-", start + 1);
            std::string ine = rr.substr(start, end);
            rr.erase(start, end);
            flag.push_back(ine);
        }
    }
}

bool switch_mode(char c, Client* clt, Channel* Chan, int flag){
    switch(c){
        case 'i':
            return Chan->setMODE(LIMIT * flag, clt);
        case 'k':
            return Chan->setMODE(KEY * flag, clt);
        case 'l':
            return Chan->setMODE(LIMIT * flag, clt);
        case 't':
            return Chan->setMODE(TOPIC * flag, clt);
        case 'o':
            return true;
        default:
            clt->rcvMsg(":server 472 " + chan->getName() + " " + c + " :is unknown mode char to me");
            return false;
    }
}

void exec_Mode(Request& rq, Server* server, Client* client){
    Channel *Chan;
    std::vector<std::string> flag;

    if (client->is_Channel(rq[1]) == false)
        return client->rcvMsg("442 " + rq[1] + " :You're not on that channel");
    Chan = server->find_channel(rq[1]);
    if (!Chan)
        return client->rcvMsg("403 " + rq[1] + " :No such channel");
    init_map(rq, flag);
    for(size_t i = 0; i < flag.size(); i++){
        int sign;
        if (flag[0] == '-')
            sign = MOINS;
        if (flag[0] == '+')
            sign = PLUS;
        else 
            continue ;
        for(size_t y = 1; y < flag[i].size(); y++)
            if (!switch_mode(flag[i][y], client, Chan, sign))
                continue ;
            if (flag[i][y] == 'k' && sign == PLUS){
                if (i + 1 >= flag.size() || flag[i + 1][0] != @){
                    clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters")
                    continue ;
                }
                chan->init_psswd(flag[i + 1]);
            }
            if (flag[i][y] == 'l' && sign == PLUS){
                if (i + 1 >= flag.size() || flag[i + 1][0] != @){
                    clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters")
                    continue ;
                }
                chan->init_limit(flag[i + 1]);
            }
            if (flag[i][y] == 'o'){
                if (i + 1 >= flag.size() || flag[i + 1][0] != @){
                    clt->rcvMsg(":server 461 " + clt->getNick() + " MODE :Not enough parameters")
                    continue ;
                }
                chan->new_op(flag[i + 1], client, flag);
            }
    }
}