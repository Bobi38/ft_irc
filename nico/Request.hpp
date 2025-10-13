#ifndef Request_HPP
# define Request_HPP
# include <iostream>
# include "Prefix.hpp"

# define BUFFER_SIZE 512 // 512 = max RFC1459 et si ca depasse ?
#include <vector>


class Channel{
    private:
        // std::string _name;
        // int flag;
        // std::vector<Client*> _member;
    public:
        Channel(std::string name);
        // std::string getName();
        // bool is_in(std::string _client_name);
        // void addClient(Client* client);
        // void rmClient(Client* Client);
        // void send_msg(std::string msg, int fd);
        ~Channel();
};

class Client{
    private:
        // int _fd;
        // std::string _nick;
        // std::string _name;
        // std::vector<Channel*>_chan;
    public:
        Client(int fd);
        // int getFd();
        // std::string getName();
        // void rmChannel(Channel* chan);
        // void addChannel(Channel* chan);
        // bool is_Channel(std::string channel);
        ~Client();
};

class Server{
	private:
		// int _port;
		// std::string _password;
		// int _server_fd;
		// std::vector<Client> _client;
		// std::vector<struct pollfd> _fds;
		// std::vector<Channel> _chan; // max, nb_user, topic, pwd
	public:
		Server() {};
		void addClient(int fd);
		void addChannel(std::string name, Client *client);
		void addFd(int fd);
		// void GoServ();
		bool check_psswd(int fd);
		// void linkClienttoChannel(Client* client, Channel* channel);
		// void unlinkClienttoChannel(Client* client, Channel* channel);
		~Server() {};
	class WrongPassword : public std::exception {
		public:
			virtual const char* what() const throw(){
				return "Password is not available!";
			}
	};
};


class Request{
	protected:
		Prefix _user;
		std::string _msg;
		std::string* _tab;
		int	_tabSize;
	public:
		Request(const std::string& str);
		Request(const Request& other);
		virtual ~Request();

		// void putNick() const;
		std::string getNick() const;
		std::string getCmd() const;
		virtual bool check(const Server* Serv) const {(void) Serv; return true;};
		virtual void exec(Server* Serv) {(void) Serv; std::cout << "ne viens pas la " << std::endl;};	
};

// int main(int a, char** b)
// {
// 	char e[52] = "PRIVMSG #text \n\t";
// 	if (a == 1)
// 		b[1] = e;
// 	for (int i = 1; i <= a; i++){
// 		std::string c = b[i];
// 		Request d(c);
// 		d.getNick();
// 	}
// }

#endif //Request.hpp