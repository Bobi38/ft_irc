#ifndef Request_HPP
# define Request_HPP
# include <iostream>
# include "Prefix.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Client;
class Server;

enum e_request{
	NO_MESSAGE,
	EMPTY_MESSAGE,
	MESSAGE_OK
};

class Request{
	protected:
		Prefix _user;
		Client* _client;
		std::string _msg;
		std::string* _tab;
		int	_tabSize;
		int _msgStatus; // exist , vide  ? (reponse enum)
		int _back; // j en ai pas besoin et toi ?
	public:
		Request(const std::string& str, Client* Client); // Le client va disparaitre d'ici 
		Request(const Request& other);
		Request() {};
		virtual ~Request();

		std::string getNick() const;
		std::string getCmd() const;
		std::string getMsg() const;
		int getMsgStatus() const;
		std::string operator[](int x) const;
		virtual bool check(const Server* Serv, const Client* clt) const {(void) clt; (void) Serv; return true;};
		virtual void exec(Server* Serv, Client* clt) {(void) clt; (void) Serv; std::cout << "ne viens pas la " << std::endl;};	
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