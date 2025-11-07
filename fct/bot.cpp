#include "Maker.hpp"
#include "Channel.hpp"
#include <iostream>
#include <fstream>

void sw_piece(bool CPiece, Bot* bot, Client* clt, Channel* TChan){
    srand(time(NULL));
    bool resultat = (rand() % 2 == 0);
    bot->addPoint((resultat == CPiece) ? LOSE : WIN, clt, TChan);
}

void prv_bot(Request& rq, Server* server, Client* client){
    bool pil_face;
    Bot* bot = dynamic_cast<Bot *>(server->find_client("bot"));
    if (rq.size_tab() == 2)
        return client->rcvMsg("envoie 'pile' ou 'face' pour jouer. Si tu veux connaitre ton score envoie 'score'", bot);
    std::cout << "msg =" << rq[MSG] << "--" << std::endl;
    if (rq[MSG] != "pile" && rq[MSG] != "face" && rq[MSG] != "score"){
        client->rcvMsg("Désolé je ne comprend pas ton message", bot);
        return client->rcvMsg("envoie 'pile' ou 'face' pour jouer. Si tu veux connaitre ton score envoie 'score'", bot);
    }
    if (rq[MSG] == "score")
        return bot->getScore(client, NULL);
    pil_face = (rq[MSG] == "pile");
    return sw_piece(pil_face, bot, client, NULL);   
}

void exec_bot(Request& rq, Server* server, Client* client) {
    bool pil_face;
    Channel *TChan;
	if (rq[0] == "PRIVMSG")
		return prv_bot(rq, server, client);
	TChan = server->find_channel(rq[1]);
	if (!TChan)
		return client->rcvMsg("403 " + rq[1] + " :No such channel");
    Bot* bot = dynamic_cast<Bot *>(server->find_client("bot"));
	if (!TChan->is_inv("bot"))
		return client->rcvMsg("Je ne suis plus dans le Channel :" + TChan->getName(), bot);
    if (rq.size_tab() == 2)
        return client->rcvMsg("envoie 'pile' ou 'face' pour jouer. Si tu veux connaitre ton score envoie 'score'", bot);

    if (rq[2] != "pile" && rq[2] != "face" && rq[2] != "score"){
        client->rcvMsg("Désolé je ne comprend pas ton message", bot);
        return client->rcvMsg("envoie 'pile' ou 'face' pour jouer. Si tu veux connaitre ton score envoie 'score'", bot);
    }
    if (rq[2] == "score")
        return bot->getScore(client, TChan);
    pil_face = (rq[2] == "pile");
    return sw_piece(pil_face, bot, client, TChan);
}