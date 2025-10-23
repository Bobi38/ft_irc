#include "Request.hpp"

std::string* split(char sep, std::string& str);

Request::Request(const std::string& str_init)
	: _user(Prefix(str_init)){
	if (str_init.empty()){
		_tab = new std::string[1];
		return ;
	}

	size_t size = str_init.size();
	int start = 0;

	if (str_init[0] == ':'){
		start = str_init.find(' ');
		start = str_init.find_first_not_of(' ', start);
	}
	else
		start = str_init.find_first_not_of(' ', start);
	std::string str = str_init.substr(start);

	// std::cout << "apres retrait user str :"<< str << std::endl;
	size_t msg = str.find(':');
	if (size - 1 > msg && msg != std::string::npos){
		_msg = str.substr(msg + 1);
		if (_msg.empty())
			_msg = EMPTY_MSG;
		msg = str.find_last_not_of(' ', msg - 1);
		str.resize(msg + 1);
	}
	
	// std::cout << "apres retrait msg str :"<< str << std::endl;
	_tab = split(' ', str);
	_tabSize = 0;
	while (!_tab[_tabSize].empty())
		_tabSize++;

	str = _tab[0];
	if (str[0] == '/'){
		str = _tab[0].substr(1);
		for (size_t i = 0; i < str.size(); i++)
			str[i] = std::toupper(str[i]);
		_tab[0] = str;
	}
}

Request::Request(const Request& other) 
	: _user(other._user), _msg(other._msg), _tabSize(other._tabSize)
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

std::string Request::getMsg() const {
	return _msg;
}

std::string Request::getNick() const{
	return _user.getNick();
}

Request::operator std::string(){
	return _msg;
}

std::string Request::operator[](int x)const{
	if (x == MSG)
		return _msg;
	if (x == -1)
		return _user.getPrefix();
	if (x < 0 || x >= _tabSize)
		return ("");
	return _tab[x];
}

int Request::size_tab(){
    size_t i = 0;
	while (!_tab[i].empty())
        i++;
    return i;
}

std::string Request::EMPTY_MSG = "\f\t\r\n\v";

// int Request::getMsgStatus() const{
// 	return _msgStatus;
// }
