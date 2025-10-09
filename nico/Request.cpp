#include "Request.hpp"

std::string* split(char sep, std::string& str);

Request::Request(std::string& str): _user(Prefix(str)){
	if (str.empty())
		return ;
	int size = str.size();
	
	int start = 0;
	if (str[0] == ':'){
		start = str.find(' ');
		start = str.find_first_not_of(' ', start);
	}

	int msg = str.rfind(':');
	if (size - 1 > msg && msg != -1){
		_msg = str.substr(msg + 1);
		msg = str.find_last_not_of(' ', msg - 1);
		_msg.resize(_msg.size() - 2);
		str.resize(msg + 1);
	}

	int end = str.find(' ', start);
	_cmd1 = str.substr(start, end - start);
	// _cmd = CMD_UNKNOW;
	// for (int i = 0; i < 15; i++)
	// 	if (_cmd1 == _fct[i])
	// 		_cmd = i;
	start = str.find_first_not_of(' ', end);
	_param = str.substr(start);
	_tab = split(' ', _param);
}

Request::~Request(){
	delete[] _tab;
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