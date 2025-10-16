#include "include/Maker.hpp"

Request* Maker::select(const std::string& str, Client *client){
	bool second = client == _wClt;
	
	int size = str.size();
	if (!size)
		return Test1::newTest1(Request ("", client));
	if (size < 2 && str[size - 2] != '\r' && str[size - 1] != '\n'){
		_buff = (second ? _buff + str : str);
		_wClt = client;
		return Test1::newTest1(Request ("", client)); // ne rien faire - en attente suite
	}
	Request rq;
	if (second) {
		rq = Request (_buff + str, client);
		_buff.clear();
	}
	else
		rq = Request(str, client);
	std::cout << rq.getCmd() << std::endl;
	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first)
			return table[i].second(rq);
	}
	return Test1::newTest1(rq);
}
