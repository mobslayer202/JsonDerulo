#include <iostream>
#include <fstream>

#include "CharReader.hpp"

int main() {

    std::ofstream getNext("test/get.txt");
    std::ofstream seeNext("test/see.txt");

    std::cout << "poopy";
    CharReader::init("JsonExamples/2.json");
    while (CharReader::canGet()){
        seeNext << CharReader::seeNextChar();
        getNext << CharReader::getNextChar();
    }
    std::cout << "poopy\n";
    CharReader::close();
    return 0;
}