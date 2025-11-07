#include "Server.hpp"

volatile sig_atomic_t stop_server = 0;

void clean_std(std::string& rest){
	for(size_t i = 0; i < rest.size(); i++){
		if (!isprint(rest[i])){
			rest.erase(i, 1);
			i = 0;
		}
	}
}

void handle_sigint(int signum) {
	(void)signum;
	stop_server = 1;
}

void send_msg(int fd, std::string msg){
	send(fd, msg.c_str(), msg.size(), 0);
}
