#include "include/Maker.hpp"

Request* Maker::select(const std::string& str) const{
	Request rq(str);
	std::cout << rq.getCmd() << std::endl;
	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first)
				return table[i].second(rq);
	}
	return Maker::error(rq);
}

Request* Maker::error(const Request& rq) {
	(void) rq;
	return NULL;
}