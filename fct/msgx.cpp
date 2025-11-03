// #include "Makerj.hpp"
// #include <vector>

// void prvmsg(Request& rq, Server* server, Client* sender){

// 	std::string msg = rq[MSG];
// 	if (msg == Request::EMPTY_MSG)
// 		msg = "";
// 	else if (msg.empty() && rq[2].empty())
// 		return sender->rcvMsg(":server 461 :Not enough parameters");
// 	else if (msg.empty())
// 		msg = rq[2];


// 	std::stringstream ss_chan(rq[1]);
// 	std::vector<std::string> vDest;
// 	std::string item;
// 	while (std::getline(ss_chan, item, ','))
// 		vDest.push_back(item);

// 	for (std::vector<std::string>::iterator it = vDest.begin(); it != vDest.end(); it++){
// 		std::string dest = *it;
		
// 		if (dest[0] == '#'|| dest[0] == '&'){
			
// 			Channel* Chan = server->find_channel(dest);
// 			if (!Chan)
// 				sender->rcvMsg(":server 403 " + dest + " :No such channel");
// 			else
// 				Chan->chan_msg(msg, sender, Chan);
// 		}
// 		else {
// 			Client* clrcv = server->find_client(dest);
// 			if (!clrcv)
// 				sender->rcvMsg(":server 401 " + dest + " :No such nick/channel");
// 			else
// 				clrcv->rcvMsg(msg, sender);
// 		}
// 	}
// }