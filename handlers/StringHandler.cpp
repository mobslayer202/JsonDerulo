#include <stdexcept>

#include "StringHandler.hpp"
#include "CharReader.hpp"

Json::JsonVal StringHandler::handle(){
    std::string seenString;

    bool strEndReached = false;
    while (!CharReader::fileEnd()){
        
        // Current Char starts at '"'
        // Increment to right after
        CharReader::increment(); 
        
        char c = CharReader::getChar();
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
        // Increment to one char after '"'
        CharReader::increment(); 
        Json::JsonVal result; // what happens when fall out of scope?
        result.value = seenString; // What happens when fall out of scope?
        return result;
    }
}