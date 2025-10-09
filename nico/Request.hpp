#ifndef Request_HPP
# define Request_HPP
# include <iostream>
# include "Prefix.hpp"

class Request{
	protected:
		Prefix _user;
		// int _cmd;
		std::string	_cmd1;
		std::string _param;
		std::string* _tab;
		std::string _target;
		std::string _msg;
		// std::string _fct[15] = {"CMD_UNKNOW","PASS","NICK","USER","JOIN", \
		// 		"PART","KICK","MODE","INVITE","TOPIC" \
		// 		,"PRIVMSG","QUIT","NAMES","LIST","OPER"};

	public:
		Request(std::string& str);
		~Request();

		void putNick() const;
		std::string& getNick() const;
		virtual bool check() const {return false;};
		virtual void exec() const {std::cout << "ne viens pas la " << std::endl;};	
	};

// int main(int a, char** b)
// {
// 	char e[52] = "PRIVMSG #text \n\t";
// 	if (a == 1)
// 		b[1] = e;
// 	for (int i = 1; i <= a; i++){
// 		std::string c = b[i];
// 		Request d(c);
// 		d.getNick();
// 	}
// }

#endif //Request.hpp