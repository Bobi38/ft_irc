#include "Makerj.hpp"
#include <vector>

std::string& Client::getBuffOut(){
	return _outBuff;
}

void Client::addBuffOut(std::string& str){
	_outBuff += str;
}

void Client::write() {
	if (_outBuff.empty())
		return;
	
	ssize_t sent = send(_fd, 
					_outBuff.c_str(), 
					_outBuff.length(), 
					0);
	
	if (sent > 0) {
		_outBuff.erase(0, sent);
	}
	else if (sent == -1) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return;
		// on vire le client ??
	}
}

void Client::rcvMsg(const std::string& msg) {
	_outBuff += msg + "/r/n";
}