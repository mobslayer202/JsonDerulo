#include <stdexcept>

#include "HandlerHelper.hpp"
#include "ObjectHandler.hpp"
#include "ArrayHandler.hpp"
#include "StringHandler.hpp"
#include "NumberHandler.hpp"
#include "BoolNullHandler.hpp"

Json::JsonVal HandlerHelper::handleAny(char c){
    if (c == '-' or std::isdigit(c)){
        NumberHandler nHandler;
        return nHandler.handle();
    }
    switch (c) {
        case '{':
            ObjectHandler oHandler;
            return oHandler.handle();
        case '[':
            ArrayHandler aHandler;
            return aHandler.handle();
        case '"':
            StringHandler sHandler;
            return sHandler.handle();
        case 't':
        case 'f':
        case 'n':
            BoolNullHandler bnHandler;
            return bnHandler.handle();
        default:
            throw std::invalid_argument("INVALID JSON"); 
    }
}