#include "Prefix.hpp"

Prefix::Prefix(const std::string& prefix){
	int size = prefix.size();
	int space = prefix.find(" ");
	if (prefix[0] != ':' | size ==  1)
        return ;
	int start = 1;
	int end = prefix.find("!", start) - 1;
	_nick = prefix.substr(start, end);

	start += end;
	if (space <= start | prefix[start] != '!')
        return ;
	start++;
	end = prefix.find("@", start);
	_user = prefix.substr(start, end - start);

	if (space <= end | prefix[end] != '@')
        return ;
	start = end + 1;
	end = prefix.find(' ', start);
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

void Prefix::putPrefix() const {if (_nick.empty()){std::cout << "no name" << std::endl; return ;} else{
	std::cout << "nick :" << _nick << std::endl;};
	if (_user.empty())std::cout << "no user"; else std::cout << "user :" << _user; std::cout << std::endl;
	if (_host.empty())std::cout << "no host"; else std::cout << "host :" << _host; std::cout << std::endl;
}

// std::string& Prefix::getPrefix() const {
//     // if (_nick.empty())
//     //     return getNick();
// 	std::string tmp = ":" + getNick();
// 	if (_user.empty() || _host.empty())
//         return tmp;
//     tmp = tmp + "!" + _user + "@" + _host;
//     return tmp;
// }
	
Prefix::~Prefix(){}

std::ostream& operator<<(std::ostream& os, const Prefix& name) {
	os << ":" << name.getNick();
	std::string tmp = name.getUser();

	if (!tmp.empty())
os << "!" << tmp;
	else
return os;
	tmp = name.getHost();
	if (!tmp.empty())
os << "@" << name.getHost();
	return os; 
}
