#ifndef Request_HPP
# define Request_HPP
# include <iostream>
# include "Prefix.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Client;
class Server;

enum e_request{
	CMD = -1,
	NO_MESSAGE,
	EMPTY_MESSAGE,
	MESSAGE_OK,
	MSG = 99,

};

class Request{
	protected:
		Prefix _user;
		std::string _msg;
		std::string* _tab;
		int	_tabSize;
	public:
		Request(const std::string& str); // Le client va disparaitre d'ici 
		Request(const Request& other);
		Request() {};
		virtual ~Request();

		std::string getNick() const;
		std::string getCmd() const;
		std::string getMsg() const;
		int size_tab();
		std::string operator[](int x);
		operator std::string();

		static std::string EMPTY_MSG;
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