#include <stdexcept>

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

Json::JsonVal ArrayHandler::handle(){
    auto array = std::make_shared<std::vector<Json::JsonVal>>(); // Don't get what this does

    bool arrEndReached = false;
    while (CharReader::canGet()){
        
        char c = CharReader::getNextChar();

        // Skip all spaces in array; none matter except in other data type(String)
        if (std::isspace(c)){ // Where is <cctype> even coming from...
            continue;
        }

        if (this->state == State::Start){
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
                nextState();
            }
            else{
                throw std::invalid_argument("INVALID JSON: Array/AfterElement"); 
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
        Json::JsonVal result; // what happens when fall out of scope?
        result.value = array; // What happens when fall out of scope?
        return result;
    }
}