#include <iostream>
#include <fstream>

#include "CharReader.hpp"
#include "Json.hpp"

// g++ main.cpp Json.cpp CharReader.cpp handlers/HandlerHelper.cpp handlers/ArrayHandler.cpp handlers/BoolNullHandler.cpp handlers/NumberHandler.cpp handlers/ObjectHandler.cpp handlers/StringHandler.cpp
int main() {

    std::ofstream getNext("test/get.txt");

    std::cout << "poopy";
    CharReader::init("JsonExamples/1.json");
    while (!CharReader::fileEnd()){
        std::cout << CharReader::getChar();
        CharReader::increment();
    }
    std::cout << "poopy\n";
    CharReader::close();

    Json::JsonVal d;

    std::cout << sizeof(d) << std::endl;
    return 0;
}