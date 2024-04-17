#include <stdexcept>

#include "BoolNullHandler.hpp"
#include "CharReader.hpp"
#include "RunSettings.hpp"

bool BoolNullHandler::handle(){
    std::string boolNullString;
    std::string expected;

    char first = CharReader::getChar();
    switch (first){
        case 't':
            expected = "true"; // W Operator overloading
            break;
        case 'f':
            expected = "false";
            break;
        case 'n':
            expected = "null";
            break;
    }

    LOGC("BoolNullHandler: (first, expected) -> '", first, "' , '" + expected + "'")
    LOG("BoolNullHandler: Starting loop")

    bool boolNullEndReached = false;
    short counter = 0;
    while (!CharReader::fileEnd()){

        LOG("BoolNullHandler: Counter -> " + std::to_string(counter))
        if (counter == expected.size()){
            if (boolNullString == expected){ 
                boolNullEndReached = true;
            }
            LOGC("BoolNullHandler: End Reached -> '", boolNullEndReached, "' " + boolNullString)
            break;
        }
        
        char c = CharReader::getChar();
        boolNullString += c;

        LOGC("BoolNullHandler: Parsing -> '", c, "'")

        counter++;
        CharReader::increment();
    }

    if (!boolNullEndReached){
        throw std::invalid_argument("INVALID JSON: illegal word, thought it was '"+expected+"' but its not"); // W operator overloading
    }
    else {
        bool result;
        if (expected == "true"){

            result = true;
        }
        else if (expected == "false"){

            result = false;
        }
        // do nothing if null?
        
        LOGC("BoolNullHandler: Finished Char -> '", CharReader::getChar(), "'")
        LOGC("BoolNullHandler: Finished -> '", result, "'")
        return result;
    }
}