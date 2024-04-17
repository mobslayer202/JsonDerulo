#include <stdexcept>

#include "StringHandler.hpp"
#include "CharReader.hpp"
#include "RunSettings.hpp"

std::string StringHandler::handle(){
    std::string seenString;

    bool strEndReached = false;

    LOGC("StringHandler: starting loop -> '", CharReader::getChar(), "'")
    while (!CharReader::fileEnd()){
        
        // Current Char starts at '"'
        // Increment to right after
        CharReader::increment(); 
        
        char c = CharReader::getChar();
        LOGC("StringHandler: parsing -> '", c, "'")
        if (c == '"'){
            LOG("StringHandler: End Reached")
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
        LOGC("StringHandler: Finished Char -> '", CharReader::getChar(), "'")
        LOG("StringHandler: Finished ->" + seenString)
        return seenString;
    }
}