#include <stdexcept>

#include "BoolNullHandler.hpp"
#include "CharReader.hpp"

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
        bool result;
        if (expected == "true"){

            result = true;
        }
        else if (expected == "false"){

            result = false;
        }
        // do nothing if null?
        
        return result;
    }
}