#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

# include "ACmd.hpp"

class PrivMsg: public ACmd{
    private:
        // std::string _target;
        // std::string _msg;
    public:
        PrivMsg(std::string msg);
        // void send_user();
        // void send_chan();
        void action ();
        void error();
        ~PrivMsg();

};

#endif