#include "Makern.hpp"

int main(){
	Server a;
	std::string str = "    TEST1 #chan      #chan2 project        :peloponeses     \n\t";
	Makern b;
	Request *rq = b.select(str);
	if (!rq)
		return 0;
	if (rq->check(&a))
		rq->exec(&a);
	delete rq;
	return 0;
}