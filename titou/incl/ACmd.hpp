#ifndef ACMD_HPP
# define ACMD_HPP

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>
# include <fstream>
# include <iomanip>
// # include "server.hpp"
# include "Prefix.hpp"

enum e_cmd{
	CMD_UNKNOW,
	PASS,
	NICK,
	USER,
	JOIN,
	PART,
	KICK,
	MODE,
	INVITE,
	TOPIC,
	PRIVMSG,
	QUIT,
	NAMES,
	LIST,
	OPER
};

class ACmd {
    protected:
        int _cmd;
		std::string* _tab;
        Prefix _user;
    public:
		ACmd(int cmd, Prefix user, std::string* tab)
      	  : _cmd(cmd), _tab(tab), _user(user) {}
        virtual void action() = 0;
        virtual void error() = 0;
        virtual ~ACmd(){};
};

#endif