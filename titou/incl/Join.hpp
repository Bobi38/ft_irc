#ifndef JOIN_HPP
# define JOIN_HPP

# include "ACmd.hpp"

class Join: public ACmd{
    private:
        // std::string _target;
    public:
        Join(std::string msg);
        void action ();
        void error();
        ~Join();

};

#endif