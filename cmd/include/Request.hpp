#ifndef Request_HPP
# define Request_HPP
# include <iostream>
# include "Prefix.hpp"
# include "Server.hpp"
# include "Client.hpp"


class Request{
	protected:
		// Prefix _user;
		Client _Clt;
		std::string _msg;
		std::string* _tab;
		int	_tabSize;
	public:
		Request(const std::string& str);
		Request(const std::string& str, const Client& Clt);
		Request(const Request& other);
		virtual ~Request();

		// void putNick() const;
		std::string getNick() const;
		std::string getCmd() const;
		virtual bool check(const Server* Serv) const {(void) Serv; return true;};
		virtual void exec(Server* Serv) {(void) Serv; std::cout << "ne viens pas la " << std::endl;};	
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