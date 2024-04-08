#include <iostream>
#include <fstream>

#include "CharReader.hpp"

int main() {

    std::ofstream getNext("test/get.txt");

    std::cout << "poopy";
    CharReader::init("JsonExamples/2.json");
    while (!CharReader::fileEnd()){
        std::cout << CharReader::getChar();
        CharReader::increment();
    }
    std::cout << "poopy\n";
    CharReader::close();
    return 0;
}