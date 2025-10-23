#include <iostream>
#include <string>
#include <curl/curl.h>

// Fonction appelée par libcurl à chaque bloc de données reçu
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Envoie une requête GET et retourne la réponse sous forme de texte
std::string httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();   // Initialise libcurl
    std::string response;

    if (curl) {
        // Indique l’URL à appeler
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Dit à libcurl où stocker la réponse
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        // Option facultative : ignorer SSL si besoin
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Exécute la requête
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Erreur curl : " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);  // Libère la mémoire
    }

    return response;
}

int main() {
    std::string apiKey = "d3sl0tpr01qpdd5k56ugd3sl0tpr01qpdd5k56v0"; // Remplace par ta clé Finnhub
    std::string symbol = "AAPL";
    std::string url = "https://finnhub.io/api/v1/quote?symbol=" + symbol + "&token=" + apiKey;

    std::string response = httpGet(url); // Envoie la requête
    std::cout << "Réponse brute de l'API :\n" << response << std::endl;
    return 0;
}