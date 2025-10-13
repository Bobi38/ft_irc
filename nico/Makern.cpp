#include "Makern.hpp"

Request* Makern::select(const std::string& str) const{
	Request rq(str);

	for (int i = 0; !table[i].first.empty(); i++) {
		if (rq.getCmd() == table[i].first)
				return table[i].second(rq);
	}
	return Makern::error(rq);
}

Request* Makern::error(const Request& rq) {
	(void) rq;
	return NULL;
}