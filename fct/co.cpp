#include "Makerj.hpp"
#include "Channel.hpp"

void exec_nick(Request& rq, Server* server, Client* client){
    Client* toto;
    toto = server->find_client(rq[1].c_str());
    if (!toto)
        client->setNick(rq[1].c_str());
    else
        client->rcvMsg("error 433 nick already use");
}

void exec_n(std::string name, Server* server, Client* client){
    Client* toto;
    toto = server->find_client(name);
    if (!toto)
        client->setNick(name);
    else
        client->rcvMsg("error 433 nick already use");
}

void exec_pass(Request& rq, Server* server, Client* client){

    if (rq.size_tab() == 6){
        std::cout << "je suis dans pass 6" << std::endl;
        std::string pss(rq[1]);
        size_t i = pss.find_first_of("\r\n", 0);
        pss.erase(i);
        std::cout << "pss= " << pss << "--" << server->getPSSD() << std::endl;
        if (pss == server->getPSSD()){
            client->setpssd();
            std::cout << "good password" << std::endl;
        }
        else{
            client->rcvMsg("464 " + client->getNick() + " :Password incorrect");
            server->dlt_client(client, client->getfd());
            return ;
        }
        std::string nick(rq[2]);
        i = nick.find_first_of("\r\n", 0);
        nick.erase(i);
        exec_n(nick, server, client);
        client->setName(rq[3]);
        client->setco();
        return ;
    }
    std::string ps(rq[1]);
    std::cout << "je suis dans PASS " << ps << " et " << rq[1] << std::endl;
    if (client->getName() != "" || client->getNick() != ""){
        client->rcvMsg("462 " + client->getNick() + " :You may not reregister");
        return;
    }
    if (rq.size_tab() < 2) {
        client->rcvMsg("461 PASS :Not enough parameters");
        return;
    }
    if (ps == server->getPSSD()){
        client->setpssd();
        std::cout << "good password" << std::endl;
    }
    else{
        client->rcvMsg("464 " + client->getNick() + " :Password incorrect");
        server->dlt_client(client, client->getfd());
    }
}


void exec_user(Request& rq, Server* server, Client* client){
    (void)server;

    // if (rq.size_tab() < 5) {
    //     client->rcvMsg("461 USER :Not enough parameters\r\n");
    //     return;
    // }
    client->setName(rq[1]);
    client->setco();
}

void exec_ping(Request& rq, Server* server, Client* client){
    (void)server;
    (void)rq;
    client->rcvMsg("PONG :server_irc");
}

void exec_CAP(Request& rq, Server* server, Client* client){
    (void)server;
    (void)rq;
    std::cout << "je suis dans CAP" << std::endl;
    if (rq.size_tab() == 3)
        client->rcvMsg(":4242 CAP * LS :");
}


// bool Client::valid_co(std::string psswd, char* buff, Server *serv){
// 	Client *toto;


// 	if (_nick == "" && _name == "" && strncmp(buff, "PASS ", 5) && _psswd == false){
// 		send_msg(_fd, "we need a nick to connect with command PASS <password>\n");
// 		return true;
// 	}
// 	if (!strncmp(buff, "PASS ", 5) && _psswd == false){
// 		std::string rest(buff + 5);
// 		clean_std(rest);
// 		if ( rest == psswd){
// 			_psswd = true;
// 			return true;
// 		}
// 		else{
// 			send_msg(_fd, "wrong password bye\n");
// 			return false;
// 		}
// 	}
// 	if (_nick == "" && strncmp(buff, "NICK ", 5)){
// 		send_msg(_fd, "we need a nick to connect with command NICK <nickname>\n");
// 		return true;
// 	}
// 	if (!strncmp(buff, "NICK ", 5)){
// 		std::string rest(buff + 5);
// 		clean_std(rest);
// 		toto = serv->find_client(rest);
// 		if (!toto){
// 			_nick = rest;
// 			return true;
// 		}
// 		send_msg(_fd, "NICK already exist, try an over \n");
// 		return true;
// 	}
// 	if (_nick != "" && _name == "" && strncmp(buff, "NAME ", 5)){
// 		send_msg(_fd, "we need a nick to connect with command NICK <nickname>\n");
// 		return true;
// 	}
// 	if (!strncmp(buff, "NAME ", 5)){
// 		std::string rest(buff + 5);
// 		clean_std(rest);
// 		toto = serv->find_client(rest);
// 		if (!toto){
// 			_name = rest;
// 			send_msg(_fd, "welcome to server IRC\n");
// 			_co = true;
// 			return true;
// 		}
// 		send_msg(_fd, "NAME already exist, try an over \n");
// 		return true;
// 	}
// 	return true;

// }