#include <stdexcept>

#include "BoolNullHandler.hpp"
#include "CharReader.hpp"

Json::JsonVal BoolNullHandler::handle(){
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

    bool boolNullEndReached = false;
    short counter = 0;
    while (!CharReader::fileEnd()){

        if (counter == expected.size()){
            if (boolNullString == expected){ 
                boolNullEndReached = true;
            }
            break;
        }
        
        char c = CharReader::getChar();
        
        boolNullString += c;

        counter++;
        CharReader::increment();
    }

    if (!boolNullEndReached){
        throw std::invalid_argument("INVALID JSON: illegal word, thought it was '"+expected+"' but its not"); // W operator overloading
    }
    else {
        Json::JsonVal result;
        if (expected == "true"){

            result.value = true;
        }
        else if (expected == "false"){

            result.value = false;
        }
        // do nothing if null?
        
        return result;
    }
}