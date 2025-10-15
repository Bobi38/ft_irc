#ifndef Part_HPP
# define Part_HPP
# include "Request.hpp"

class Part : public Request {
public:
	Part(Client* client, Server* server, const std::vector<std::string>& args);
	~Part();
	Part(const Part& other);
	Part* operator=(const Part& other);
	BackMsg execute();
};

#endif // Part.hpp