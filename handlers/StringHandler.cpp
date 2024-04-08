#include <stdexcept>

#include "StringHandler.hpp"
#include "CharReader.hpp"

Json::JsonVal StringHandler::handle(){
    std::string seenString;

    bool strEndReached = false;
    while (CharReader::canGet()){
        
        char c = CharReader::getNextChar();
        if (c == '"'){
            strEndReached = true;
            break;
        }
        else{
            seenString += c;
        }
    }

    if (!strEndReached){
        throw std::invalid_argument("INVALID JSON: end of file reached before string end");
    }
    else{
        Json::JsonVal result; // what happens when fall out of scope?
        result.value = seenString; // What happens when fall out of scope?
        return result;
    }
}