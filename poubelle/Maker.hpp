#ifndef MAKER_HPP
# define MAKER_HPP

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>
# include <fstream>
# include <iomanip>
# include "ACmd.hpp"
# include "Join.hpp"
# include "PrivMsg.hpp"

class Maker{
    private:
        ACmd* makeJoin(std::string msg);
        ACmd* makePrivMsg(std::string msg);
    public:
        Maker();
        ~Maker();
        ACmd* makeCmd(int type, std::string msg);
};

#endif