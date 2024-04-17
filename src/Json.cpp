#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <stdexcept>

#include "Json.hpp"
#include "HandlerHelper.hpp"
#include "CharReader.hpp"
#include "RunSettings.hpp"

Json::Json(const char* filePath){

    LOG("Json: Starting Parse")
    CharReader::init(filePath);
    CharReader::increment(); // Put real data in buffer
    char c = CharReader::getChar(); // Breaks on empty file
    this->data = HandlerHelper::handleAny(c);
    LOG("Json: Parse Completed!")
}

void Json::makeFile(const char* filePath){
    //std::ofstream output("JsonExamples/result.json");
    auto jsonArr = std::get<std::shared_ptr<std::vector<JsonVal>>>(data.value);
    auto d = std::get<std::string>((*jsonArr)[0].value);
    std::cout << d;
}