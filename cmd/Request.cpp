#include "Request.hpp"

std::string* split(char sep, std::string& str);

Request::Request(const std::string& str_init): _user(Prefix(str_init)), _back(0){
	if (str_init.empty())
		return ;

	int size = str_init.size();
	int start = 0;

	if (str_init[0] == ':'){
		start = str_init.find(' ');
		start = str_init.find_first_not_of(' ', start);
	}
	else
		start = str_init.find_first_not_of(' ', start);
	std::string str = str_init.substr(start);

	// std::cout << "apres retrait user str :"<< str << std::endl;
	int msg = str.rfind(':');
	if (size - 1 > msg && msg != -1){
		_msg = str.substr(msg + 1);
		msg = str.find_last_not_of(' ', msg - 1);
		_msg.resize(_msg.size() - 2);
		str.resize(msg + 1);
	}
	else
		str.resize(size - 2);
	
	// std::cout << "apres retrait msg str :"<< str << std::endl;
	_tab = split(' ', str);
	_tabSize = 0;
	while (!_tab[_tabSize].empty())
		_tabSize++;
}

Request::Request(const Request& other) 
	: _user(other._user), _msg(other._msg), _tabSize(other._tabSize), _back(0)
{
	if (other._tab && _tabSize > 0) {
		_tab = new std::string[_tabSize];
		for (int i = 0; i < _tabSize; i++) {
			_tab[i] = other._tab[i];
		}
	} else {
		_tab = NULL;
	}
}

Request::~Request() {
	if (_tab)
		delete[] _tab;
}

std::string Request::getCmd() const {
	return _tab[0];
}

std::string Request::getNick() const{
	return _user.getNick();
}

std::string Request::operator[](int x)const{
	if (x < 0 || x > _tabSize)
		return ("");
	return _tab[x];
}