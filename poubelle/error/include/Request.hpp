#ifndef REQUEST_HPP
# define REQUEST_HPP
# include <vector>
# include <iostream>
# include <Client.hpp>
# include <Server.hpp>
# include "BackMsg.hpp"

class Request {
protected:
	std::vector<std::string> _args;
	Client* _client;
	Server* _server;
	
public:
	Request(Client* client, Server* server, const std::vector<std::string>& args);
	Request(const Request& other);
	Request* operator=(const Request& other) const;
	virtual ~Request();
	
	virtual BackMsg execute() = 0;
	BackMsg validateMinArgs(int nb) const;
};

#endif // Request.hpp