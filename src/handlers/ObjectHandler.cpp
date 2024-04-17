#include <stdexcept>
#include <memory>

#include "ObjectHandler.hpp"
#include "CharReader.hpp"
#include "HandlerHelper.hpp"
#include "StringHandler.hpp"

void ObjectHandler::nextState(){ // Shorten to casting increment way?
    switch(this->state){
        case State::Start:
            this->state = State::Colon;
            break;
        case State::Colon:
            this->state = State::B4Val;
            break;
        case State::B4Val:
            this->state = State::AfterVal;
            break;
        case State::AfterVal:
            this->state = State::AfterComma;
            break;
        case State::AfterComma:
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

    while (!CharReader::fileEnd()){
        
        char c = CharReader::getChar();

        // Skip all spaces in object; none matter except in other data type(String)
        if (std::isspace(c)){ // Where is <cctype> even coming from...
            continue;
        }

        // Deal with char based on state
        if (this->state == State::Start){ // If else vs switch? switch "break;" will be confused = will need scuffed workaround

            // Current Char starts at '{'
            // Increment to right after
            CharReader::increment(); 
            c = CharReader::getChar(); // Starts right after '{'

            if (c == '"'){
                StringHandler sHandler;
                key = sHandler.handle(); 
                nextState();

                // Make sure key is not duplicate
                if ((*object).find(key) != (*object).end()) {

                    throw std::invalid_argument("INVALID JSON: Duplicate keys");
                }
            }
            else if (c == '}'){
                objEndReached = true;
                break;
            }
            else{
                std::string sawChar(1, c);
                throw std::invalid_argument("INVALID JSON: Object/Start -> '" + sawChar + "'"); 
            }
        }
        else if (this->state == State::Colon){
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
            val = HandlerHelper::handleAny(c);
        }
        else if (this->state == State::AfterVal){

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
            if (c == '"'){
                StringHandler sHandler;
                key = sHandler.handle(); 
                nextState();
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
        // Increment to one char after '}'
        CharReader::increment(); 
        return object;
    }
}