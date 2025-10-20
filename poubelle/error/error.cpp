# include <sstream>

enum e_error{
	RPL_WELCOME = 001,
	RPL_YOURHOST = 002,	
	RPL_CREATED = 003,
	RPL_MYINFO = 004,
	ERR_NEEDMOREPARAMS = 461,
	ERR_NOSUCHCHANNEL = 403,
	ERR_NOTONCHANNEL = 442,
	ERR_CHANNELISFULL = 471,
	RPL_TOPIC = 332,
	RPL_NAMREPLY = 353, 
};

std::string formatCode(int code) {
	std::ostringstream oss;
	if (code < 10)
		oss << "00" << code;
	else if (code < 100)
		oss << "0" << code;
	else
		oss << code;
	return oss.str();
}

std::string msg_error(int code, const std::string& client, 
	const std::string& target, const std::string& msg) {
		std::ostringstream oss;
		oss << ":" << "server.name" << " " << formatCode(code) << " " << client;
		if (!target.empty())
			oss << " " << target;
		oss << " :" << msg << "\r\n";
		return oss.str();
}

#include<iostream>

int main(){
	std::cout << msg_error(RPL_MYINFO, "bruno", "Valerie", "bouge");
}



