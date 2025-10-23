#ifndef MAKERJ_HPP
# define MAKERJ_HPP
# include <sstream>
# include "Request.hpp"

void test2(Request& rq, Server* server, Client* client);
void prvmsg(Request& rq, Server* server, Client* client);
void exec_quit(Request& rq, Server* serv, Client* clt);
void exec_join(Request& rq, Server* server, Client* client);
void exec_part(Request& rq, Server* server, Client* client);
void exec_kick(Request& rq, Server* server, Client* client);
void test3(Request& rq, Server* server, Client* client);
void invit(Request& rq, Server* server, Client* client);
void mode(Request& rq, Server* server, Client* client);
void topic(Request& rq, Server* server, Client* client);


typedef std::pair<std::string, void (*)(Request&, Server*, Client*)> Level;

class Maker
{
private:
	Level table[16];
	Client* _wClt;
	std::string _buff;
public:
	Maker();
	Maker(const Maker& other);
	Maker* operator=(const Maker& other);
	~Maker();

	void select(const std::string& str, Server* server, Client* client);
};

#endif