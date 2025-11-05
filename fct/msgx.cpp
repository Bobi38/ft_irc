#include "Makerj.hpp"
#include <vector>

void prvmsg(Request& rq, Server* server, Client* sender){

	std::string msg = rq[MSG];
	if (msg == Request::EMPTY_MSG)
		msg = "";
	else if (msg.empty() && rq[2].empty())
		return sender->rcvMsg(":server 461 :Not enough parameters");
	else if (msg.empty())
		msg = rq[2];


	std::stringstream ss_chan(rq[1]);
	std::vector<std::string> vDest;
	std::string item;
	while (std::getline(ss_chan, item, ','))
		vDest.push_back(item);

	for (std::vector<std::string>::iterator it = vDest.begin(); it != vDest.end(); it++){
		std::string dest = *it;
		
		if (dest[0] == '#'|| dest[0] == '&'){
			
			Channel* Chan = server->find_channel(dest);
			if (!Chan)
				sender->rcvMsg(":server 403 " + dest + " :No such channel");
			else
				Chan->chan_msg(msg, sender, Chan);
		}
		else {
			Client* clrcv = server->find_client(dest);
			if (!clrcv)
				sender->rcvMsg(":server 401 " + dest + " :No such nick/channel");
			else{
					if (clrcv->getNick() == "bot")
						return exec_bot(rq, server, sender);
				clrcv->rcvMsg(msg, sender);
			}
		}
	}
}

std::string& Client::getBuffOut(){
	return _outBuff;
}

void Client::addBuffOut(std::string& str){
	_outBuff += str;
}

void Client::write() {
	if (_outBuff.empty())
		return;
	
	ssize_t sent = send(_fd, 
					_outBuff.c_str(), 
					_outBuff.length(), 
					0);
	
	if (sent > 0) {
		_outBuff.erase(0, sent);
		if (!_outBuff.empty())
			std::cout << "demi message" << std::endl;
	}
	else if (sent == -1)
		std::cerr << "Erreur send: " << strerror(errno) << std::endl;

}

void Client::rcvMsg(const std::string& msg) {
	_outBuff += msg + "\r\n";
}

void Client::rcvMsg(const std::string& msg, Client* client) {
	std::string msg_temp = msg;
	if (msg_temp == Request::EMPTY_MSG)
		msg_temp = "";
	if (client == NULL)
		return rcvMsg(":server 401 " + getNick());
	msg_temp = client->getMe() + " PRIVMSG : " + msg_temp;
	rcvMsg(msg_temp);
}
