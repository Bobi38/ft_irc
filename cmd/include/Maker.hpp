#ifndef MAKER_HPP
# define MAKER_HPP
# include "Request.hpp"
# include "Topic.hpp"
# include "Join.hpp"
# include "Test1.hpp"
# include <utility>

typedef std::pair<std::string, Request* (*)(const Request&)> Level;

class Makern
{
private:
	Level table[16];
public:
	Makern() {
		table[0] = Level("PASS", Test1::newTest1);
		table[1] = Level("NICK", Test1::newTest1);
		table[2] = Level("USER", Test1::newTest1);
		table[3] = Level("JOIN", Join::newJoin);
		table[4] = Level("PART", Test1::newTest1);
		table[5] = Level("KICK", Test1::newTest1);
		table[6] = Level("MODE", Test1::newTest1);
		table[7] = Level("INVITE", Test1::newTest1);
		table[8] = Level("PRIVMSG", Test1::newTest1);
		table[9] = Level("QUIT", Test1::newTest1);
		table[10] = Level("NAMES", Test1::newTest1);
		table[11] = Level("OPER", Test1::newTest1);
		table[12] = Level("LIST", Test1::newTest1);
		table[13] = Level("TOPIC", Topic::newTopic);
		table[14] = Level("TEST1", Test1::newTest1);
		table[15] = Level("", NULL);
	};
	~Makern() {};

	static Request* error(const Request& rq);
	Request* select(const std::string& str) const;
};

#endif