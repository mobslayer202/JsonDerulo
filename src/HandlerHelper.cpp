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
            { // Scope without function or class. Whole switch statement is one scope, so need to 
                // make scopes in each Case to have each case to be one scope.
                // Need scope to avoid "cross initialization"
                ObjectHandler oHandler;
                result.value = oHandler.handle();
                break;
            }
        case '[':
            {   
                ArrayHandler aHandler;
                result.value = aHandler.handle();
                break;
            }
        case '"':
            {
                StringHandler sHandler;
                result.value = sHandler.handle();
                break;
            }
        case 't':
        case 'f':
        case 'n':
            {
                BoolNullHandler bnHandler;
                result.value = bnHandler.handle();
                break;
            }
        default:
            throw std::invalid_argument("INVALID JSON"); 
    }
    return result;
}