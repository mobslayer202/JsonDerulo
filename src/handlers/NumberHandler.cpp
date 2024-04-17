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
            LOG("NumberHandler: Normal -> AfterNormal")
            this->state = State::AfterNormal;
            break;
        case State::AfterNormal:
            LOG("NumberHandler: AfterNormal -> AfterDecimal")
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
        else if (this->state == State::Normal){
            LOGC("NumberHandler/Normal: -> '", c, "'")
            if (std::isdigit(c)){
                nextState();
                numberString += c;
            }
            else {
                if (numberString[0] == '-'){
                    std::string sawChar(1, c);
                    throw std::invalid_argument("INVALID JSON: Number/Normal -> '" + sawChar + "'"); 
                }
                else {
                    LOGC("NumberHandler/Normal: End Reached -> '", c, "'")
                    numEndReached = true;
                    break; 
                }
                
            }
        }
        else if (this->state == State::AfterNormal){
            if (c == '.'){
                LOGC("NumberHandler/AfterNormal: -> '", c, "'")
                nextState();
                numberString += c;
            }
            else {
                LOGC("NumberHandler/AfterNormal: End Reached -> '", c, "'")
                numEndReached = true;
                break; 
            }
        }
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