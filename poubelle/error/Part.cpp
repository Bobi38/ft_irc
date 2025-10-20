#include "Part.hpp"

Part::Part(Client* client, Server* server, const std::vector<std::string>& args)
	: Request(client, server, args) {}

BackMsg Part::execute() {
	BackMsg validation = validateMinArgs(2);
	if (!validation.isSuccess())
		return validation;

	std::string channel = _args[0];
	
	bool isOnChannel = false;
	if (!isOnChannel) {
		return BackMsg(
			ERR_NOTONCHANNEL,
			channel,
			"You're not on that channel"
		);
	}
	
	std::cout << _client->getName() << " parts " << channel << std::endl;
	return BackMsg(true);
}

Part::~Part() {
}

Part::Part(const Part& other){
    (void) other;
}

Part* Part::operator=(const Part& other) {
	return (NULL);
}