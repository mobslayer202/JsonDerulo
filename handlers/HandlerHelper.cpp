#include <stdexcept>

#include "HandlerHelper.hpp"
#include "ObjectHandler.hpp"
#include "ArrayHandler.hpp"
#include "StringHandler.hpp"
#include "NumberHandler.hpp"
#include "BoolNullHandler.hpp"

Json::JsonVal HandlerHelper::handleAny(char c){
    Json::JsonVal result; // What happen when fall out of scope?
    if (c == '-' or std::isdigit(c)){
        NumberHandler nHandler;
        result.value = nHandler.handle();
    }
    switch (c) {
        case '{':
            ObjectHandler oHandler;
            result.value = oHandler.handle();
        case '[':
            ArrayHandler aHandler;
            result.value = aHandler.handle();
        case '"':
            StringHandler sHandler;
            result.value = sHandler.handle();
        case 't':
        case 'f':
        case 'n':
            BoolNullHandler bnHandler;
            result.value = bnHandler.handle();
        default:
            throw std::invalid_argument("INVALID JSON"); 
    }
}