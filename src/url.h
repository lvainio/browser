#pragma once

#include <string>

// https://url.spec.whatwg.org/
class Url {
public:
    explicit Url(const std::string& rawUrl);

private:
    void parse(const std::string& rawUrl);

    std::string url_;
    std::string scheme_;
    std::string host_;
    std::string path_;
    std::string query_;
    std::string fragment_;
    std::string port_;
};