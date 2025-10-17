#include "Makerj.hpp"

bool check_join(Request& rq){
    for(int i = 0; rq[i]; i++){
        if (tab[i][0] != "#")
            return false;
    }
    return true;
}

bool init_chan_key(Request& rq,  std::vector<std::string name>& chan, std::vector<std::string key>& key){
    
}

void exec_join(Request& rq, Server* server, Client* client){
    std::vector<std::string name> chan;
    std::vector<std::string key> key;
    if (!client || !check_join(rq))

}