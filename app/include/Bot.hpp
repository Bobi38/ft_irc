#ifndef BOT_HPP
# define BOT_HPP

# include <map>
# include <utility>
# include "Client.hpp"
#include "Channel.hpp"


enum e_coin{
	WIN,
	LOSE
};

typedef std::map<Client*,std::pair<int,int> > sco;

class Bot: public Client{
	private:
		sco _score;
	public:
		Bot();
		void addClient(Client *clt);
		void rmClient(Client *clt);
		void addPoint(int result, Client *clt, Channel* Chan);
		void getScore(Client *clt, Channel* chan);
		~Bot(){};
};

#endif
