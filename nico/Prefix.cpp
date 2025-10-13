#include "Prefix.hpp"

Prefix::Prefix(const std::string& prefix) {
	size_t size = prefix.size();
	size_t space = prefix.find(" ");

	if (prefix.empty() || prefix[0] != ':' || size == 1) {
		_nick = "";
		_user = "";
		_host = "";
		return;
	}
	
	size_t start = 1;
	size_t end = prefix.find("!", start);
	
	if (end == std::string::npos || end >= space) {
		end = (space != std::string::npos) ? space : size;
		_nick = prefix.substr(start, end - start);
		_user = "";
		_host = "";
		return;
	}
	
	_nick = prefix.substr(start, end - start);
	
	start = end + 1;
	end = prefix.find("@", start);
	
	if (end == std::string::npos || end >= space) {
		_user = "";
		_host = "";
		return;
	}

	_user = prefix.substr(start, end - start);
	
	start = end + 1;
	end = (space != std::string::npos) ? space : size;
	_host = prefix.substr(start, end - start);
}

Prefix::Prefix(): _nick(""), _user(""), _host("") {}

Prefix::Prefix(const Prefix& p): _nick(p.getNick()), _user(p.getUser()), _host(p.getHost()) {}

std::string Prefix::getNick()const {
    return _nick;
}

std::string Prefix::getUser()const {
    return _user;
}

std::string Prefix::getHost()const {
    return _host;
}

void Prefix::putPrefix() const {
	if (_nick.empty()) {
		std::cout << "no name" << std::endl;
		return;
	}
	
	std::cout << "nick: " << _nick << std::endl;
	
	if (_user.empty())
		std::cout << "no user" << std::endl;
	else
		std::cout << "user: " << _user << std::endl;
	
	if (_host.empty())
		std::cout << "no host" << std::endl;
	else
		std::cout << "host: " << _host << std::endl;
}

std::string Prefix::getPrefix() const {
	if (_nick.empty())
		return ":";
	
	std::string tmp = ":" + _nick;
	
	if (_user.empty() || _host.empty())
		return tmp;
	
	tmp = tmp + "!" + _user + "@" + _host;
	return tmp;
}

Prefix::~Prefix(){}

std::ostream& operator<<(std::ostream& os, const Prefix& name) {
	std::string nick = name.getNick();
	if (nick.empty())
		return os;

	os << ":" << nick;

	std::string user = name.getUser();
	if (!user.empty()) {
		os << "!" << user;
		
		std::string host = name.getHost();
		if (!host.empty())
			os << "@" << host;
	}
	return os;
}
