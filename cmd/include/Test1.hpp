#ifndef TEST1_HPP
# define TEST1_HPP
# include "Request.hpp"

class Test1 : public Request
{
	private:
		// int error;
	public:
		Test1(const Request& rq);
		Test1(const Test1& other);
		Test1& operator=(const Test1& other);
		~Test1();	

		bool check(const Server* serv) const;
		void exec(Server* Serv);
		static Request* newTest1(const Request& rq);
};

#endif //Test1.hpp