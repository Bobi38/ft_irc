#ifndef MAKERJ_HPP
# define MAKERJ_HPP
# include "Request.hpp"

void test2(Request* rq, Server* server, Client* client);

void test3(Request* rq, Server* server, Client* client);

typedef std::pair<std::string, void (*)(Request*, Server*, Client*)> Level;

class Maker
{
private:
	Level table[16];
	Client* _wClt;
	std::string _buff;
public:
	Maker() {
		table[0] = Level("PASS", test2);
		table[1] = Level("NICK", test2);
		table[2] = Level("USER", test2);
		table[3] = Level("JOIN", test2);
		table[4] = Level("PART", test2);
		table[5] = Level("KICK", test2);
		table[6] = Level("MODE", test3);
		table[7] = Level("INVITE", test2);
		table[8] = Level("PRIVMSG", test2);
		table[9] = Level("QUIT", test2);
		table[10] = Level("NAMES", test2);
		table[11] = Level("OPER", test2);
		table[12] = Level("LIST", test2);
		table[13] = Level("TOPIC", test2);
		table[14] = Level("TEST1", test2);
	};
	~Maker() {};

	// Request* select(const std::string& str, Client* client);
	void select(const std::string& str, Server* server, Client* client);
};

#endif