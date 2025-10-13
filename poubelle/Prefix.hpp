#ifndef PREFIX_HPP
# define PREFIX_HPP
# include <iostream>


class Prefix{
	private:
		std::string _nick;
		std::string _user;
		std::string _host;
		// int 		_fd;
	public:
        Prefix();
		Prefix(const std::string& prefix);
		Prefix(const Prefix& p);
		~Prefix();

		std::string getNick()const;
		std::string getUser()const;
		std::string getHost()const;
        // std::string& getPrefix() const;
		void putPrefix() const;
};

std::ostream& operator<<(std::ostream& os, const Prefix& name);

#endif //prefix.hpp
