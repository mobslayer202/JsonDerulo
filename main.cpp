#include <iostream>
#include <fstream>
#include <unordered_map>

#include "CharReader.hpp"
#include "Json.hpp"

// g++ main.cpp Json.cpp CharReader.cpp handlers/HandlerHelper.cpp handlers/ArrayHandler.cpp handlers/BoolNullHandler.cpp handlers/NumberHandler.cpp handlers/ObjectHandler.cpp handlers/StringHandler.cpp
int main() {

    std::ofstream getNext("test/get.txt");

    std::cout << "poopy";
    CharReader::init("JsonExamples/my.json");
    while (!CharReader::fileEnd()){
        std::cout << CharReader::getChar();
        CharReader::increment();
    }
    std::cout << "poopy\n";
    CharReader::close();

    Json d("JsonExamples/2.json");
    //d.makeFile("JsonOutput/v2.json");
    Json::JsonVal topj = d;
    std::shared_ptr<std::unordered_map<std::string, Json::JsonVal>> topP = topj;
    std::unordered_map<std::string, Json::JsonVal> top = *topP;

    Json::JsonVal nameVal = top["name"];
    std::string nameVal1 = nameVal;

    std::string nameVal2 = top["name"];

    std::cout << nameVal2 << "\n";

    std::cout << (std::string) top["name"] << "\n";
    //std::unordered_map<std::string, Json::JsonVal> top2 = *topj; Don't work (*) dereference doesnt make it cast from shared ptr
    
    

    //std::cout << sizeof(d) << std::endl;
    return 0;
}