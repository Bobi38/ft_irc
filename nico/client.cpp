// #ifndef REQUEST_HPP
# define REQUEST_HPP

# include <vector>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <iostream>
# include <fstream>
# include <iomanip>
# include <ctime>
# include <stdexcept>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h> 
# include <poll.h>


enum e_cmd{
	CMD_UNKNOW,
	PASS,
	NICK,
	USER,
	JOIN,
	PART,
	KICK,
	MODE,
	INVITE,
	TOPIC,
	PRIVMSG,
	QUIT,
	NAMES,
	LIST,
	OPER
};

class Prefix{
	private:
		std::string _nick;
		std::string _user;
		std::string _host;
	public:
		Prefix(const std::string& prefix){
			int size = prefix.size();
			int space = prefix.find(" ");
			if (prefix[0] != ':' | size ==  1)
				return ;
			int start = 1;
			int end = prefix.find("!", start) - 1;
			_nick = prefix.substr(start, end);

			start += end;
			if (space <= start | prefix[start] != '!')
				return ;
			start++;
			end = prefix.find("@", start);
			_user = prefix.substr(start, end - start);

			if (space <= end | prefix[end] != '@')
				return ;
			_host = prefix.substr(end + 1);
		};
		Prefix() : _nick(""), _user(""), _host("") {};
		Prefix(const Prefix& p): _nick(p.getNick()), _user(p.getUser()), _host(p.getHost()) {};
		std::string getNick()const {return _nick;};
		std::string getUser()const {return _user;};
		std::string getHost()const {return _host;};
		~Prefix(){};	
};

std::ostream& operator<<(std::ostream& os, const Prefix& name) {
	os << ":" << name.getNick();
	std::string tmp = name.getUser();

	if (!tmp.empty())
		os << "!" << tmp;
	else
		return os;
	tmp = name.getHost();
	if (!tmp.empty())
		os << "@" << name.getHost();
	return os; 
}

class Request{
	private:
		int	 _cmd;
		Prefix _user;
		std::string _param;
		std::string _target;
		std::string _msg;
		std::string _fct[15];

	public:
		Request(std::string& str): _user(Prefix(str)),
			_fct({"CMD_UNKNOW","PASS","NICK","USER","JOIN", \
				"PART","KICK","MODE","INVITE","TOPIC" \
				,"PRIVMSG","QUIT","NAMES","LIST","OPER"}){
		if (str.empty())
			return ;
		int size = str.size();
		int start = 0;
		if (str[0] == ':'){
			start = str.find(' ');
			start = str.find_first_not_of(' ', start);
		}
		
		int msg = str.rfind(':');
		if (size - 1 < msg){
			_msg = str.substr(size - msg, msg);
			msg = str.find_last_not_of(' ', msg + 1);
			str[msg + 1] = '\0';
		}

		int end = str.find(' ', start);
		std::string tmp = str.substr(start, end - start);
		for (int i = 0; i < 15; i++)
			if (tmp == _fct[i])
				_cmd = i;
		};

		int getFd();
		~Request();

		std::string getNick() const {return _user.getNick();};
};

// #endif
