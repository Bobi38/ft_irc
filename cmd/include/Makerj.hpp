#ifndef MAKER_HPP
# define MAKER_HPP
# include "Request.hpp"
# include "Topic.hpp"
# include "Join.hpp"
# include "Test1.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include <map>

typedef void (*fct_ptr)(Request&, Client*, Server*);

void test2(Request& a, Client* b, Server* c){
    (void) c;
    if (b)
        std::cout << b->getName() << std::endl;
    if (!a[0].empty()){
        for (int i = 0; !a[i].empty(); i++)
            std::cout << a[i] << std::endl;
    }
};

class Maker
{
private:
	std::map<std::string, fct_ptr> dico;
public:
	Maker() {
        dico["TEST2"] = &test2;
	};
	~Maker() {};

	static Request* error(const Request& rq);
	Request* select(const std::string& str) const;
};

#endif