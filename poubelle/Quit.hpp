#ifndef QUIT_HPP
# define QUIT_HPP
// # include "Request.hpp"

class Quit : public Request
{
	private:

	public:
		Quit(const Request& rq);
		Quit(const Quit& other);
		Quit& operator=(const Quit& other);
		~Quit();	

		bool check(const Server* serv, const Client* clt) const;
		void exec(Server* Serv, Client* clt);
		static Request* newQuit(const Request& rq);
		void send_all(Client* clt);
		void fd_send(Client* clt, std::set<int>& list);
};

#endif