#include <stdexcept>

#include "NumberHandler.hpp"
#include "CharReader.hpp"

void NumberHandler::nextState(){
    switch (this->state){
        case State::Start:
            this->state = State::Normal;
            break;
        case State::Normal:
            this->state = State::AfterNormal;
            break;
        case State::AfterNormal:
            this->state = State::AfterDecimal;
            break;
    }
}

Json::JsonVal NumberHandler::handle(){
    std::string numberString;

    bool numEndReached = false;
    while (!CharReader::fileEnd()){

        // Current Char starts at first char of number
        char c = CharReader::getChar();

        if (this->state == State::Start){
            if (c == '-' or std::isdigit(c)){
                nextState();
                numberString += c;
            }
            else {
                throw std::invalid_argument("INVALID JSON: Number/Start"); 
            }
        }
        else if (this->state == State::Normal){
            if (std::isdigit(c)){
                nextState();
                numberString += c;
            }
            else {
                throw std::invalid_argument("INVALID JSON: Number/Normal"); 
            }
        }
        else if (this->state == State::AfterNormal){
            if (c == '.'){
                nextState();
                numberString += c;
            }
            else {
                numEndReached = true;
                break; 
            }
        }
        else if (this->state == State::AfterDecimal){
            if (std::isdigit(c)){
                numberString += c;
            }
            else {
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
        Json::JsonVal result;
        result.value = std::stod(numberString);
        return result;
    }
}