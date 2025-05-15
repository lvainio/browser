#include <iostream>

#include "url.h"

void show(std::string body) {
    bool in_tag = false;
    for (char ch : body) {
        if (ch == '<') {
            in_tag = true;
        } else if (ch == '>') {
            in_tag = false;
        } else if (!in_tag) {
            std::cout << ch;
        }
    }
    std::cout << std::endl;
}

int main() {
    std::size_t testvar = 5;

    std::cout << sizeof testvar << std::endl;

    std::cout << "A very nice web browser!" << std::endl;

    Url url("https://browser.engineering/examples/example1-simple.html");

    std::cout << url.toString() << std::endl;

    std::string body = url.request();

    std::cout << "------------\nPRINTING HTML BODY:\n------------ "
              << std::endl;

    show(body);
}