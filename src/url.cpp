#include "url.h"
#include <iostream>
#include <curl/curl.h>

// https://url.spec.whatwg.org/
// FIXME: implement tests
Url::Url(const std::string& rawUrl) {

    // FIXME: clean up and better naming.
    
    // TODO: what is size_t
    auto pos = rawUrl.find("://");

    scheme_ = rawUrl.substr(0, pos);

    std::string rest = rawUrl.substr(pos+3, rawUrl.size());

    // TODO: what is npos
    auto slashPos = rest.find('/');
    if (slashPos != std::string::npos) {
        host_ = rest.substr(0, slashPos);
        path_ = rest.substr(slashPos, rest.size());
    }
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    ((std::string*)userp)->append((char*)contents, total_size);
    return total_size;
}

void Url::request() {
    std::string fullUrl = this->toString();

    CURL *curl;
    CURLcode res;
    std::string response_body;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());

        res = curl_easy_perform(curl);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

        if (res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Request sent successfully!" << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cout << "NO CURL" << std::endl;
    }

    curl_global_cleanup();
}

std::string Url::toString() {
    return scheme_ + "://" + host_ + path_;
}