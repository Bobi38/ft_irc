#ifndef BACKMSG_HPP
# define BACKMSG_HPP
# include <iostream>
#include <sstream>

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

class BackMsg {
private:
	bool _ok;
	int _errorCode;
	std::string _msg;
	std::string _target;

public:
	BackMsg(bool ok = true);
	BackMsg(int errorCode, const std::string& target, const std::string& msg);
	BackMsg(const BackMsg& other);
	BackMsg operator=(const BackMsg& other) const;
	~BackMsg();

	bool isSuccess() const;
	int getErrorCode() const;
	const std::string& getMessage() const;
	const std::string& getTarget() const;
	std::string toIRCMessage(const std::string& clientNick) const;
};

#endif // backMsg