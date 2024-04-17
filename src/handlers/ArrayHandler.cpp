#include <stdexcept>

#include "ArrayHandler.hpp"
#include "CharReader.hpp"
#include "HandlerHelper.hpp"
#include "RunSettings.hpp"

void ArrayHandler::nextState(){
    switch (this->state){
        case State::Start:
            LOG("ArrayHandler: Start -> AfterElement")
            this->state = State::AfterElement;
            break;
        case State::AfterElement:
            LOG("ArrayHandler: AfterElement -> AfterComma")
            this->state = State::AfterComma;
            break;
        case State::AfterComma:
            LOG("ArrayHandler: AfterComma -> AfterElement")
            this->state = State::AfterElement;
            break;
    }
}


std::shared_ptr<std::vector<Json::JsonVal>> ArrayHandler::handle(){
    auto array = std::make_shared<std::vector<Json::JsonVal>>(); // Don't get what this does

    bool arrEndReached = false;
    bool justStarted = true;
    LOGC("ArrayHandler: starting loop -> '", CharReader::getChar(), "'")
    while (!CharReader::fileEnd()){

        char c = CharReader::getChar();

        // Skip all spaces in array; none matter except in other data type(String)
        if (std::isspace(c)){ // Where is <cctype> even coming from...
            LOGC("ArrayHandler: Continuing -> '", c, "'")
            CharReader::increment(); 
            continue;
        }
        
        if (this->state == State::Start){

            if (justStarted){
                // Current Char starts at '['
                // Increment to right after
                CharReader::increment(); 
                c = CharReader::getChar();
                justStarted = false;
            }

            LOGC("ArrayHandler/Start: Just Got Char -> '", c, "'")

            // Skip all spaces in array; none matter except in other data type(String)
            if (std::isspace(c)){ // Where is <cctype> even coming from...
                LOGC("ArrayHandler/Start: Continuing -> '", c, "'")
                CharReader::increment(); 
                continue;
            }

            if (c == ']'){
                LOG("ArrayHandler/Start: End Reached")
                arrEndReached = true;
                break;
            }
            Json::JsonVal element = HandlerHelper::handleAny(c);
            (*array).push_back(element);
            nextState();
            LOGC("ArrayHandler/Start: Element Gotten -> '", CharReader::getChar(), "'")
        }
        else if (this->state == State::AfterElement){
            
            LOGC("ArrayHandler/AfterElement: Char -> '", c, "'")
            if (c == ']'){
                LOG("ArrayHandler/AfterElement: End Reached")
                arrEndReached = true;
                break;
            }
            else if (c == ','){
                LOG("ArrayHandler/AfterElement: Going Next State")
                nextState();
                CharReader::increment(); 
            }
            else{
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Array/AfterElement -> '" + sawChar + "'"); 
            }
        }
        else if (this->state == State::AfterComma){
            LOGC("ArrayHandler/AfterComma: B4GetElement -> '", c, "'")
            Json::JsonVal element = HandlerHelper::handleAny(c);
            (*array).push_back(element);
            nextState();
            LOGC("ArrayHandler/AfterComma: Element Gotten -> '", CharReader::getChar(), "'")
        }
    }

    if (!arrEndReached){
        throw std::invalid_argument("INVALID JSON: end of file reached before array end");
    }
    else{
        LOGC("ArrayHandler: Finishing -> '", CharReader::getChar(), "'")
        // Increment to one char after ']'
        CharReader::increment(); 
        return array;
    }
}