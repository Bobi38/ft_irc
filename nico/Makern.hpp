#ifndef MAKERN_HPP
# define MAKERN_HPP
# include "Request.hpp"
# include "Topic.hpp"
# include "Join.hpp"
# include "Test1.hpp"
# include <utility>


typedef std::pair<std::string, Request* (*)(const Request&)> Level;

class Makern
{
private:
	Level table[18];
public:
	Makern() {
		table[0] = Level("TOPIC", Topic::newTopic);
		table[1] = Level("JOIN", Join::newJoin);
		table[2] = Level("TEST1", Test1::newTest1);
		table[3] = Level("", NULL);
	};
	~Makern() {};

	static Request* error(const Request& rq);
	Request* select(const std::string& str) const;
};

#endif