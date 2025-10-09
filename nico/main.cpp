#include "topic.hpp"

// enum e_cmd{
// 	CMD_UNKNOW,
// 	PASS,
// 	NICK,
// 	USER,
// 	JOIN,
// 	PART,
// 	KICK,
// 	MODE,
// 	INVITE,
// 	TOPIC,
// 	PRIVMSG,
// 	QUIT,
// 	NAMES,
// 	LIST,
// 	OPER
// };

Request* parse(std::string& str){
    Request rq(str);
    return topic::newRequest(rq);
}

int main(){
    std::string str = "TOPIC #chan :project";
    Request *rq = parse(str);
    if (rq->check())
        rq->exec();
    // delete rq; //pourtant il le faut
    return 0;
}