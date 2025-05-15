#include "url.h"

#include <curl/curl.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

// https://url.spec.whatwg.org/
// FIXME: implement tests
Url::Url(const std::string &rawUrl) {
    url_ = rawUrl;

    auto pos = rawUrl.find("://");

    scheme_ = rawUrl.substr(0, pos);

    std::string rest = rawUrl.substr(pos + 3, rawUrl.size());

    auto slashPos = rest.find('/');
    if (slashPos != std::string::npos) {
        host_ = rest.substr(0, slashPos);
        path_ = rest.substr(slashPos, rest.size());
    }
}

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    ((std::string *)userp)->append((char *)contents, total_size);
    return total_size;
}

std::string Url::request() {
    std::string fullUrl = this->toString();

    CURL *curl;
    CURLcode res;
    std::string response_body;
    std::string response_headers;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(res)
                      << std::endl;
        } else {
            std::cout << "=== Response Headers ===\n"
                      << response_headers << "\n";
            std::cout << "=== Response Body ===\n" << response_body << "\n";
        }

        // parse status line
        size_t pos = response_headers.find("\r\n");
        std::string statusLine = (pos != std::string::npos)
                                     ? response_headers.substr(0, pos)
                                     : response_headers;
        std::istringstream stream(statusLine);

        std::string httpVersion;
        std::string statusCode;
        std::string statusMessage;

        stream >> httpVersion >> statusCode;
        std::getline(stream, statusMessage);
        statusMessage.erase(0, 1);

        // parse headers
        // FIXME: refactor into a separate function.
        std::unordered_map<std::string, std::vector<std::string>> headerMap;
        std::istringstream stream2(response_headers);
        std::string line;

        // Skip the first line (status line)
        std::getline(stream2, line);

        while (std::getline(stream2, line)) {
            // Remove trailing \r (from \r\n line endings)
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }

            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                std::string key = line.substr(0, colonPos);
                std::string value = line.substr(colonPos + 1);

                // Trim whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                // Add value to vector (supporting multiple values for the same
                // header)
                headerMap[key].push_back(value);
            }
        }

        for (const auto &header : headerMap) {
            std::cout << header.first << ": ";
            for (const auto &value : header.second) {
                std::cout << value << ", ";
            }
            std::cout << std::endl;
        }

        assert(headerMap.find("transfer-encoding") == headerMap.end());
        assert(headerMap.find("content-encoding") == headerMap.end());

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL" << std::endl;
    }

    curl_global_cleanup();

    return response_body;
}

std::string Url::toString() { return scheme_ + "://" + host_ + path_; }