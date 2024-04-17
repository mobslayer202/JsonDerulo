#include <stdexcept>

#include "NumberHandler.hpp"
#include "CharReader.hpp"
#include "RunSettings.hpp"

void NumberHandler::nextState(){
    switch (this->state){
        case State::Start:
            LOG("NumberHandler: Start -> Normal")
            this->state = State::Normal;
            break;
        case State::Normal:
            LOG("NumberHandler: Normal -> AfterDecimal")
            this->state = State::AfterDecimal;
            break;
    }
}

double NumberHandler::handle(){
    std::string numberString;

    LOGC("NumberHandler: Starting loop -> '", CharReader::getChar(), "'")
    bool numEndReached = false;
    while (!CharReader::fileEnd()){

        // Current Char starts at first char of number
        char c = CharReader::getChar();

        if (this->state == State::Start){
            LOGC("NumberHandler/Start: -> '", c, "'")
            if (c == '-' or std::isdigit(c)){
                nextState();
                numberString += c;
            }
            else {
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Number/Start -> '" + sawChar + "'"); 
            }
        }
        // Starting with char right after digit or '-'
        // Should see digit, '.', or something else
        else if (this->state == State::Normal){
            LOGC("NumberHandler/Normal: -> '", c, "'")
            if (std::isdigit(c)){
                numberString += c;
            }
            else if (c == '.'){
                LOGC("NumberHandler/Normal: -> '", c, "'")
                char last = numberString[numberString.size()-1];

                // Throw error if '.' is right after '-'
                if(!std::isdigit(last)){ 
                    std::string sawChar(1, c);
                    throw std::invalid_argument("INVALID JSON: Number/Normal -> '" + sawChar + "'"); 
                }

                nextState();
                numberString += c;
            }
            else {
                char last = numberString[numberString.size()-1];

                // Throw error if INVALID_CHAR (not '.' or digit) is right after '-'
                if(!std::isdigit(last)){ 
                    std::string sawChar(1, c);
                    throw std::invalid_argument("INVALID JSON: Number/Normal -> '" + sawChar + "'"); 
                }
                // No decimal number
                else {
                    LOGC("NumberHandler/Normal: End Reached -> '", c, "'")
                    numEndReached = true;
                    break; 
                }
            }
        }
        // Starting with char right after '.'
        // Should see digit or something else
        else if (this->state == State::AfterDecimal){
            if (std::isdigit(c)){
                LOGC("NumberHandler/AfterDecimal: -> '", c, "'")
                numberString += c;
            }
            else {
                LOGC("NumberHandler/AfterDecimal: End Reached -> '", c, "'")
                numEndReached = true;
                break;
            }
        }

        CharReader::increment();
    }

    if (!numEndReached){
        throw std::invalid_argument("INVALID JSON: end of file reached before number end"); // What if only number? - last char is part of number - bug
    }
    else {
        LOG("NumberHandler: Finished -> " + numberString)
        return std::stod(numberString);
    }
}