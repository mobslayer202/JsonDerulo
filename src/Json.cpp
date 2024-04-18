#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <stdexcept>
//#include <option>

#include "Json.hpp"
#include "HandlerHelper.hpp"
#include "CharReader.hpp"
#include "RunSettings.hpp"
#include "JsonPrinter.hpp"

Json::Json(const std::string& filePath){

    JLOG("Json Constructor: Starting Parse")
    CharReader::init(filePath);
    CharReader::increment(); // Put real data in buffer
    char c = CharReader::getChar(); // Breaks on empty file
    this->data = HandlerHelper::handleAny(c);
    JLOG("Json Constructor: Parse Completed!")
}

void Json::makeFile(const std::string& filePath){
    
    JsonPrinter jPrinter(filePath);
    jPrinter.printJson(data, 0);
}