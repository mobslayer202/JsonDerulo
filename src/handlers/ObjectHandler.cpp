#include <stdexcept>
#include <memory>

#include "ObjectHandler.hpp"
#include "CharReader.hpp"
#include "HandlerHelper.hpp"
#include "StringHandler.hpp"
#include "RunSettings.hpp"

void ObjectHandler::nextState(){ // Shorten to casting increment way?
    switch(this->state){
        case State::Start:
            LOG("ObjectHandler: Start -> Colon")
            this->state = State::Colon;
            break;
        case State::Colon:
            LOG("ObjectHandler: Colon -> B4Val")
            this->state = State::B4Val;
            break;
        case State::B4Val:
            LOG("ObjectHandler: B4Val -> AfterVal")
            this->state = State::AfterVal;
            break;
        case State::AfterVal:
            LOG("ObjectHandler: AfterVal -> AfterComma")
            this->state = State::AfterComma;
            break;
        case State::AfterComma:
            LOG("ObjectHandler: AfterComma -> Colon")
            this->state = State::Colon;
            break;
    }
}

// can have an empty string as a key
// make sure to handle duplicate keys
std::shared_ptr<std::unordered_map<std::string, Json::JsonVal>> ObjectHandler::handle(){
    auto object = std::make_shared<std::unordered_map<std::string, Json::JsonVal>>();

    bool objEndReached = false;
    std::string key;
    Json::JsonVal val;

    LOGC("ObjectHandler: Starting Loop -> '", CharReader::getChar(), "'")
    while (!CharReader::fileEnd()){
        
        char c = CharReader::getChar();

        // Skip all spaces in object; none matter except in other data type(String)
        if (std::isspace(c)){ // Where is <cctype> even coming from...
            LOGC("ObjectHandler: Continuing -> '", c, "'")
            CharReader::increment(); 
            continue;
        }

        // Deal with char based on state
        if (this->state == State::Start){ // If else vs switch? switch "break;" will be confused = will need scuffed workaround

            // Current Char starts at '{'
            // Increment to right after
            CharReader::increment(); 
            c = CharReader::getChar(); // Starts right after '{'

            LOGC("ObjectHandler/Start: Just Got Char -> '", c, "'")

            // Skip all spaces in array; none matter except in other data type(String)
            if (std::isspace(c)){ // Where is <cctype> even coming from...
                LOGC("ObjectHandler/Start: Continuing -> '", c, "'")
                CharReader::increment(); 
                continue;
            }

            if (c == '"'){ // BUG: need to increment
                StringHandler sHandler;
                key = sHandler.handle(); 
                nextState();
                LOG("ObjectHandler/Start: Key Gotten -> \"" + key + "\"")

                // Make sure key is not duplicate
                if ((*object).find(key) != (*object).end()) {

                    throw std::invalid_argument("INVALID JSON: Duplicate keys");
                }
            }
            else if (c == '}'){
                LOG("ObjectHandler/Start: End Reached")
                objEndReached = true;
                break;
            }
            else{
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Object/Start -> '" + sawChar + "'"); 
            }
        }
        else if (this->state == State::Colon){
            LOGC("ObjectHandler/Colon: Char -> '", c, "'")
            if (c == ':'){
                nextState();
                CharReader::increment(); 
            }
            else{
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Object/Colon -> '" + sawChar + "'"); 
            }
        }
        else if (this->state == State::B4Val){
            LOGC("ObjectHandler/B4Val: B4Handle -> '", c, "'")
            val = HandlerHelper::handleAny(c);
            LOGC("ObjectHandler/B4Val: AfterHandle -> '", c, "'")
        }
        else if (this->state == State::AfterVal){

            LOGC("ObjectHandler/AfterVal: Char -> '", c, "'")
            (*object)[key] = val;
            if (c == ','){
                nextState();
                CharReader::increment(); 
            }
            else if (c == '}'){
                objEndReached = true;
                break;
            }
            else {
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Object/AfterVal -> '" + sawChar + "'"); 
            }
        }
        else if (this->state == State::AfterComma){

            LOGC("ObjectHandler/AfterComma: Char -> '", c, "'")
            if (c == '"'){
                StringHandler sHandler;
                key = sHandler.handle(); 
                nextState();
                LOGC("ObjectHandler/AfterComma: AfterHandle -> '", c, "'")

                // Make sure key is not duplicate
                if ((*object).find(key) != (*object).end()) {

                    throw std::invalid_argument("INVALID JSON: Duplicate keys");
                }
            }
            else{
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Object/AfterComma -> '" + sawChar + "'"); 
            }
        }
    }

    if (!objEndReached){
        throw std::invalid_argument("INVALID JSON: end of file reached before object end");
    }
    else {
        LOGC("ObjectHandler: Finishing -> '", CharReader::getChar(), "'")
        // Increment to one char after '}'
        CharReader::increment(); 
        return object;
    }
}