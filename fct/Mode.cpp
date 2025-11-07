#include "Maker.hpp"
#include "Channel.hpp"

static void init_map(Request& rq,  std::vector<std::string> &flag, std::vector<std::string> &arg){
	if (rq.size_tab() < 3)
		return ;
	for(int i = 2; i < rq.size_tab(); i++){
		std::string rr = rq[i];
		if (rr[0] != '-' && rr[0] != '+'){
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

void mode_flag(Channel* chan, Client* clt){
    std::string msg =":server 324 " + clt->getNick() + " " + chan->getName();
    if (chan->mode_act() == true)
        msg = msg + " +";
    if (chan->getMODE(KEY) == true)
        msg = msg + "k";
    if (chan->getMODE(INVITE_ONLY) == true)
        msg = msg + "i";
    if (chan->getMODE(TOPIC) == true)
        msg = msg + "t";
    if (chan->getMODE(LIMIT) == true){
        std::ostringstream oss;
		oss << chan->getlimit();
		std::string str = oss.str();
        msg = msg + "l " + str;
    }
    clt->rcvMsg(msg);
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
	if (rq.size_tab() == 2)
		return mode_flag(Chan, client);
	init_map(rq, flag, arg);
    std::vector<std::string>::iterator z = arg.begin();
	for(size_t i = 0; i < flag.size(); i++){
		int sign;
		if (flag[i][0] == '-')
			sign = -1;
		else
			sign = 1;
		for(size_t y = 1; y < flag[i].size(); y++){
			switch (flag[i][y]){
		        case 'i': Chan->setMOD(INVITE_ONLY * sign, client); break;
                case 'b': Chan->mod_ban(sign, client, z); break ;
		        case 'k': Chan->init_psswd(sign, client, z); break ;
		        case 'l': Chan->init_limit(sign, client, z); break ;
		        case 't': Chan->setMOD(TOPIC * sign, client); break ;
		        case 'o': Chan->mod_op(sign, client, z); break ;
		        default:
		        	client->rcvMsg(":server 472 " + Chan->getName() + " " + flag[i][y] + " :is unknown mode char to me");
	        }
		}
	}
}
