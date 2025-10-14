#ifndef TOPIC_HPP
# define TOPIC_HPP
# include "Request.hpp"

class Topic : public Request
{
	private:

	public:
		Topic(const Request& rq);
		Topic(const Topic& other);
		Topic& operator=(const Topic& other);
		~Topic();	

		bool check(const Server* serv, const Client* clt) const;
		void exec(Server* Serv, Client* clt);
		static Request* newTopic(const Request& rq);
};

#endif //Topic.hpp