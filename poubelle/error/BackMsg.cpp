# include "BackMsg.hpp"

BackMsg::BackMsg(bool ok = true) 
	: _ok(ok), _errorCode(0), _msg(""), _target("") {
}
	
BackMsg::BackMsg(int errorCode, const std::string& target, const std::string& msg)
	: _ok(false), _errorCode(errorCode), _msg(msg), _target(target) {
}

bool BackMsg::isSuccess() const {
	return _ok;
}

int BackMsg::getErrorCode() const {
	return _errorCode;
}

const std::string& BackMsg::getMessage() const {
	return _msg;
}

const std::string& BackMsg::getTarget() const {
	return _target;
}

std::string formatCode(int code) {
	std::ostringstream oss;
	if (code < 10)
		oss << "00" << code;
	else if (code < 100)
		oss << "0" << code;
	else
		oss << code;
	return oss.str();
}

std::string BackMsg::toIRCMessage(const std::string& Nick) const {
	if (_ok)
		return "";
	std::ostringstream oss;
	oss << ":" << "server.name" << " " << formatCode(_errorCode) << " " << Nick;
	if (!_target.empty())
		oss << " " << _target;
	oss << " :" << _msg << "\r\n";
	return oss.str();
}

BackMsg::BackMsg(const BackMsg& other) 
	: _ok(other._ok), _errorCode(0), _msg(""), _target("") {
}

BackMsg BackMsg::operator=(const BackMsg& other) const{
	return BackMsg();
}

BackMsg::~BackMsg() {}