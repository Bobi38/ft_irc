#ifndef MAKERJ_HPP
# define MAKERJ_HPP
# include <sstream>
# include "Request.hpp"
# include <map>

void test2(Request& rq, Server* server, Client* client);
void prvmsg(Request& rq, Server* server, Client* client);
void exec_quit(Request& rq, Server* serv, Client* clt);
void exec_join(Request& rq, Server* server, Client* client);
void exec_part(Request& rq, Server* server, Client* client);
void exec_kick(Request& rq, Server* server, Client* client);
void exec_list(Request& rq, Server* server, Client* client);
void exec_pass(Request& rq, Server* server, Client* client);
void exec_nick(Request& rq, Server* server, Client* client);
void exec_user(Request& rq, Server* server, Client* client);
void exec_ping(Request& rq, Server* server, Client* client);
void exec_CAP(Request& rq, Server* server, Client* client);
void exec_Mode(Request& rq, Server* server, Client* client);
void exec_Names(Request& rq, Server* server, Client* client);
void test3(Request& rq, Server* server, Client* client);
void invit(Request& rq, Server* server, Client* client);
void who(Request& rq, Server* server, Client* client);
void topic(Request& rq, Server* server, Client* client);


typedef std::pair<std::string, void (*)(Request&, Server*, Client*)> Level;

class Maker
{
private:
	Level table[18];
	std::string _buff;
public:
	Maker();
	Maker(const Maker& other);
	Maker* operator=(const Maker& other);
	~Maker();

	void select(std::string& str, Server* server, Client* client);
};

#endif