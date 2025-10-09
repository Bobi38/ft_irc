#ifndef TOPIC_HPP
# define TOPIC_HPP
# include "Request.hpp"

class topic : public Request
{
	private:

	public:
		topic(const Request& rq);
		topic(const topic& other);
		topic& operator=(const topic& other);
		~topic();	

		bool check() const;
		void exec() const;
		static Request* newRequest(const Request& rq);
};

#endif //topic.hpp