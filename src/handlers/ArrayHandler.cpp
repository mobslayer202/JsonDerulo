#include <stdexcept>
#include <iostream>

#include "ArrayHandler.hpp"
#include "CharReader.hpp"
#include "HandlerHelper.hpp"

void ArrayHandler::nextState(){
    switch (this->state){
        case State::Start:
            this->state = State::AfterElement;
            break;
        case State::AfterElement:
            this->state = State::AfterComma;
        case State::AfterComma:
            this->state = State::AfterElement;
    }
}

std::shared_ptr<std::vector<Json::JsonVal>> ArrayHandler::handle(){
    auto array = std::make_shared<std::vector<Json::JsonVal>>(); // Don't get what this does

    bool arrEndReached = false;
    
    while (!CharReader::fileEnd()){

        char c = CharReader::getChar();

        // Skip all spaces in array; none matter except in other data type(String)
        if (std::isspace(c)){ // Where is <cctype> even coming from...
            continue;
        }
        
        if (this->state == State::Start){

            // Current Char starts at '['
            // Increment to right after
            CharReader::increment(); 
            c = CharReader::getChar();

            if (c == ']'){
                arrEndReached = true;
                break;
            }
            Json::JsonVal element = HandlerHelper::handleAny(c);
            (*array).push_back(element);
            nextState();
        }
        else if (this->state == State::AfterElement){
            
            if (c == ']'){
                arrEndReached = true;
                break;
            }
            else if (c == ','){
                std::cout << "saw comma!" << std::endl;
                nextState();
                CharReader::increment(); 
            }
            else{
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Array/AfterElement -> '" + sawChar + "'"); 
            }
        }
        else if (this->state == State::AfterComma){
            Json::JsonVal element = HandlerHelper::handleAny(c);
            (*array).push_back(element);
            nextState();
        }
    }

    if (!arrEndReached){
        throw std::invalid_argument("INVALID JSON: end of file reached before array end");
    }
    else{
        // Increment to one char after ']'
        CharReader::increment(); 
        return array;
    }
}