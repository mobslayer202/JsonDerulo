#include <stdexcept>

#include "HandlerHelper.hpp"
#include "ObjectHandler.hpp"
#include "ArrayHandler.hpp"
#include "StringHandler.hpp"
#include "NumberHandler.hpp"
#include "BoolNullHandler.hpp"
#include "RunSettings.hpp"

Json::JsonVal HandlerHelper::handleAny(char c){
    
    LOGC("HandlerHelper: Char -> '", c, "'")
    Json::JsonVal result; // What happen when fall out of scope?
    if (c == '-' or std::isdigit(c)){
        LOG("HandlerHelper: Handling Number")
        NumberHandler nHandler;
        result.value = nHandler.handle();
    }
    else{
        switch (c) {
            case '{':
                { // Scope without function or class. Whole switch statement is one scope, so need to 
                    // make scopes in each Case to have each case to be one scope.
                    // Need scope to avoid "cross initialization"
                    LOG("HandlerHelper: Handling Object")
                    ObjectHandler oHandler;
                    result.value = oHandler.handle();
                    break;
                }
            case '[':
                {   
                    LOG("HandlerHelper: Handling Array")
                    ArrayHandler aHandler;
                    result.value = aHandler.handle();
                    break;
                }
            case '"':
                {
                    LOG("HandlerHelper: Handling String")
                    StringHandler sHandler;
                    result.value = sHandler.handle();
                    break;
                }
            case 't':
            case 'f':
            case 'n':
                {
                    LOG("HandlerHelper: Handling BoolNull")
                    BoolNullHandler bnHandler;
                    result.value = bnHandler.handle();
                    break;
                }
            default:
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: HandlerHelper -> '" + sawChar + "'"); 
        }
    }
    
    LOG("HandlerHelper: Finished")
    return result;
}