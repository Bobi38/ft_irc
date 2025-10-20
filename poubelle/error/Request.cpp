#include "Request.hpp"

Request::Request(Client* client, Server* server, const std::vector<std::string>& args) 
	: _args(args), _client(client), _server(server) {
}

BackMsg Request::validateMinArgs(int nb) const{
	if (_args.size() < nb) {
		return BackMsg(
			ERR_NEEDMOREPARAMS,
			_args.empty() ? "*" : _args[0],
			"Not enough parameters"
		);
	}
	return BackMsg(true);
}

Request::Request(const Request& other) 
	: _args(NULL), _client(NULL), _server(NULL) {
}

Request* Request::Request::operator=(const Request& other) const{
	return NULL;
}

Request::~Request() {
}
