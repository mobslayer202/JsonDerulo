#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <stdexcept>

#include "Json.hpp"
#include "HandlerHelper.hpp"
#include "CharReader.hpp"

Json::Json(const char* filePath){

    CharReader::init(filePath);
    CharReader::increment(); // Put real data in buffer
    char c = CharReader::getChar(); // Breaks on empty file
    this->data = HandlerHelper::handleAny(c);
}