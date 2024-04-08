#include <stdexcept>

#include "HandlerHelper.hpp"
#include "ObjectHandler.hpp"

Json::JsonVal HandlerHelper::handleAny(char c){
    if (c == '-' or std::isdigit(c)){
        // NumberHandler nHandler;
        // return nHandler.handle();
    }
    switch (c) {
        case '{':
            ObjectHandler oHandler;
            return oHandler.handle();
        case '[':
            // ArrayHandler aHandler;
            // return aHandler.handle();
        case '"':
            // StringHandler sHandler;
            // return sHandler.handle();
        case 't':
            // TrueHandler tHandler;
            // return tHandler.handle();
        case 'f':
            // FalseHandler fHandler;
            // return fHandler.handle();
        case 'n':
            // NullHandler nHandler;
            // return nHandler.handle();
        default:
            throw std::invalid_argument("INVALID JSON"); 
    }
}