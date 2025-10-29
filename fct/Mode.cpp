#include "Makerj.hpp"
#include "Channel.hpp"

static void init_map(Request& rq,  std::vector<std::string> &flag, std::vector<std::string> &arg){
	if (rq.size_tab() < 3)
		return ;
	for(int i = 2; i < rq.size_tab(); i++){
		std::string rr = rq[i];
		if (rr[0] != '-' && rr[0] != '+'){
			rr = '@' + rr;
			arg.push_back(rr);
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
    arg.push_back("");
    flag.push_back("");
}

bool switch_mode(char c, Client* clt, Channel* Chan, int flag){
	switch(c){
		case 'i':
			return Chan->setMOD(INVITE_ONLY * flag, clt);
        case 'b':
			return Chan->is_in(clt->getNick());
		case 'k':
			return Chan->setMOD(KEY * flag, clt);
		case 'l':
			return Chan->setMOD(LIMIT * flag, clt);
		case 't':
			return Chan->setMOD(TOPIC * flag, clt);
		case 'o':
			return Chan->is_in(clt->getNick());
		default:
			clt->rcvMsg(":server 472 " + Chan->getName() + " " + c + " :is unknown mode char to me");
			return false;
	}
}



void exec_Mode(Request& rq, Server* server, Client* client){
	Channel *Chan;
	std::vector<std::string> flag;
    std::vector<std::string> arg;

	if (client->is_Channel(rq[1]) == false)
		return client->rcvMsg("442 " + rq[1] + " :You're not on that channel");
	Chan = server->find_channel(rq[1]);
	if (!Chan)
		return client->rcvMsg("403 " + rq[1] + " :No such channel");
    // if (rq.size() == 2) // faire fonction 
    //     return mode_flag(Chan, client);
	init_map(rq, flag, arg);
    size_t z = 0;
	for(size_t i = 0; i < flag.size(); i++){
		int sign;
		if (flag[i][0] == '-')
			sign = -1;
		else
			sign = 1;
		for(size_t y = 1; y < flag[i].size(); y++){
			if (!switch_mode(flag[i][y], client, Chan, sign))
				continue ;
            // if ((flag[i][y] == 'k' || flag[i][y] == 'l') && sign == 1 && z >= arg.size()){
			// 		client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
			//  		continue ;                
            // }
            // if (flag[i][y] == 'o' && z >= arg.size()){
			// 		client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
			//  		continue ;                
            // }
            // if (flag[i][y] == 'b' && z >= arg.size() && sign == -1){
			// 		client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
			//  		continue ; 
            // }
            // if (!switch_mode(flag[i][y], client, Chan, sign))
			// 	continue ;
			if (flag[i][y] == 'k' && sign == 1){
				if (z >= arg.size()){
					client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
					continue ;
				}
				Chan->init_psswd(arg[z]);
                z++;
			}
			if (flag[i][y] == 'l' && sign == 1){
				if (z >= arg.size()){
					client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
					continue ;
				}
				Chan->init_limit(arg[z]);
                z++;
			}
			if (flag[i][y] == 'o'){
				if ((i + 1 >= flag.size())){
					client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
					continue ;
				}
				Chan->new_op(arg[z], client, sign);
                z++
			}
            if (flag[i][y] == 'b'){
				if ((i + 1 >= flag.size()) && sign == -1){
					client->rcvMsg(":server 461 " + client->getNick() + " MODE :Not enough parameters");
					continue ;
				}
                if ((i + 1 >= flag.size()) && sign == 1){
                    // faire fonction affichage des BAN 
					continue ;
				}
				Chan->new_ban(arg[z], client, sign);
                z++
			}
		}
	}
}