#include <iostream>
#include "url.h"

int main() {
    std::cout << "A very nice web browser!" << std::endl;

    Url url("http://example.org/");

    std::cout << url.toString() << std::endl;

    url.request();
}