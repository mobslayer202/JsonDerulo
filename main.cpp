#include <iostream>

#include "CharReader.hpp"

int main() {
    std::cout << "poopy";
    CharReader::init("JsonExamples/2.json");
    while (CharReader::canGet()){
        std::cout << CharReader::getNextChar();
    }
    std::cout << "poopy\n";
    return 0;
}