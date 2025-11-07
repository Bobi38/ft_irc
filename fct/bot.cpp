#include "Makerj.hpp"
#include "Channel.hpp"
#include <iostream>
#include <fstream>
// #include <curl/curl.h>

// size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
//     size_t totalSize = size * nmemb;
//     output->append((char*)contents, totalSize);
//     return totalSize;
// }

// std::string httpGet(const std::string& url) {
//     CURL* curl = curl_easy_init();
//     std::string response;

//     if (curl) {
//         // Indique l’URL à appeler
//         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//         // Dit à libcurl où stocker la réponse
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//         // Option facultative : ignorer SSL si besoin
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
//         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

//         // Exécute la requête
//         CURLcode res = curl_easy_perform(curl);
//         if (res != CURLE_OK) {
//             std::cerr << "Erreur curl : " << curl_easy_strerror(res) << std::endl;
//         }

//         curl_easy_cleanup(curl);  // Libère la mémoire
//     }

//     return response;
// }

// void open_api(std::string& api){
//     std::string buff;
//     std::ifstream in(".api");
// }

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

    // std::string apiKey = "d3sl0tpr01qpdd5k56ugd3sl0tpr01qpdd5k56v0"; // Remplace par ta clé Finnhub
    // std::string symbol = "AAPL";
    // std::string url = "https://finnhub.io/api/v1/quote?symbol=" + symbol + "&token=" + apiKey;

    // std::string response = httpGet(url); // Envoie la requête
    // std::cout << "Réponse brute de l'API :\n" << response << std::endl;
}