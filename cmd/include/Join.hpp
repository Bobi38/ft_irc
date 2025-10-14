#ifndef JOIN_HPP
# define JOIN_HPP
# include "Request.hpp"

class Join : public Request
{
	private:

	public:
		Join(const Request& rq);
		Join(const Join& other);
		Join& operator=(const Join& other);
		~Join();	

		bool check(const Server* serv, const Client* clt) const;
		void exec(Server* Serv, Client* clt);
		static Request* newJoin(const Request& rq);
};

#endif //Join.hpp