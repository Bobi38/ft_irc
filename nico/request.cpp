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
			start = end + 1;
			end = prefix.find(' ', start);
			_host = prefix.substr(start, end - start);
		};
		Prefix() : _nick(""), _user(""), _host("") {};
		Prefix(const Prefix& p): _nick(p.getNick()), _user(p.getUser()), _host(p.getHost()) {};
		std::string getNick()const {return _nick;};
		std::string getUser()const {return _user;};
		std::string getHost()const {return _host;};
		void getPrefix() const {if (_nick.empty()){std::cout << "no name" << std::endl; return ;} else{
			std::cout << "nick :" << _nick << std::endl;};
			if (_user.empty())std::cout << "no user"; else std::cout << "user :" << _user; std::cout << std::endl;
			if (_host.empty())std::cout << "no host"; else std::cout << "host :" << _host; std::cout << std::endl;
		};
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
		std::string _fct[15] = {"CMD_UNKNOW","PASS","NICK","USER","JOIN", \
				"PART","KICK","MODE","INVITE","TOPIC" \
				,"PRIVMSG","QUIT","NAMES","LIST","OPER"};

	public:
		Request(std::string& str): _user(Prefix(str)){
		if (str.empty())
			return ;
		int size = str.size();
	
		int start = 0;
		if (str[0] == ':'){
			start = str.find(' ');
			start = str.find_first_not_of(' ', start);
		}

		int msg = str.rfind(':');
		if (size - 1 > msg){
			_msg = str.substr(msg + 1);
			msg = str.find_last_not_of(' ', msg - 1);
			_msg.resize(_msg.size() - 2);
			str.resize(msg + 1);
		}
		
		int end = str.find(' ', start);
		std::string tmp = str.substr(start, end - start);
		_cmd = CMD_UNKNOW;
		for (int i = 0; i < 15; i++)
			if (tmp == _fct[i])
				_cmd = i;
		start = str.find_first_not_of(' ', end);
		_param = str.substr(start);
		};

		int getFd();
		~Request(){};

		void getNick() const {_user.getPrefix(); std::cout << _cmd << ": param :" << _param;
			std::cout << "\nmessage :" << _msg << std::endl;};
	};

int main(int a, char** b)
{
	char e[52] = ":nic!serv@local USER psswrd :1234567\n\t";
	if (a == 1)
		b[1] = e;
	for (int i = 1; i <= a; i++){
		std::string c = b[i];
		Request d(c);
		d.getNick();
	}
}

// #endif
