#include "Request.hpp"

std::string* split(char sep, std::string& str);

Request::Request(const std::string& str_init): _user(Prefix(str_init)){
	if (str_init.empty())
		return ;
	int size = str_init.size();
	
	int start = 0;
	if (str_init[0] == ':'){
		start = str_init.find(' ');
		start = str_init.find_first_not_of(' ', start);
	}

	std::string str = str_init.substr(start);
	int msg = str.rfind(':');
	if (size - 1 > msg && msg != -1){
		_msg = str.substr(msg + 1);
		msg = str.find_last_not_of(' ', msg - 1);
		_msg.resize(_msg.size() - 2);
		str.resize(msg + 1);
	}

	int end = str.find(' ', start);
	_cmd1 = str.substr(start, end - start);
	start = str.find_first_not_of(' ', end);
	_param = str.substr(start);
	_tab = split(' ', _param);
	_tabSize = 0;
	while (!_tab[_tabSize].empty())
		_tabSize++;
}

Request::Request(const Request& other) 
	: _user(other._user), _cmd1(other._cmd1), _param(other._param), \
		_msg(other._msg), _tabSize(other._tabSize)
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
	return _cmd1;
}

void Request::putNick() const {
	_user.putPrefix();
	std::cout << _cmd1 << ": param :" << _param;
	std::cout << "\nmessage :" << _msg << std::endl;
}

// std::string& Request::getNick() const {
// 	std::string back = _user.getPrefix();
// 	std::cout << _cmd1 << ": param :" << _param;
// 	std::cout << "\nmessage :" << _msg << std::endl;
// 	return back;
// }