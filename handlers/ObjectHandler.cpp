#include <stdexcept>
#include <memory>

#include "ObjectHandler.hpp"
#include "CharReader.hpp"
#include "HandlerHelper.hpp"

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
Json::JsonVal ObjectHandler::handle(){
    auto object = std::make_shared<std::unordered_map<std::string, Json::JsonVal>>();

    bool objEndReached = false;
    std::string key;
    Json::JsonVal val;
    while (CharReader::canGet()){
        
        char c = CharReader::getNextChar();

        /*if (c == '}'){ // Incorrect: finishes object even if '}' is in an invalid spot
            break;
        }*/

        // Skip all spaces in object; none matter except in other data type(String)
        if (std::isspace(c)){ // Where is <cctype> even coming from...
            continue;
        }

        // Deal with char based on state
        if (this->state == State::Start){ // If else vs switch? switch "break;" will be confused = will need scuffed workaround
            if (c == '"'){
                // key = StringHandler::handle().value;
                // nextState();
                // if ((*object).find(key) != (*object).end()) {throw std::invalid_argument("INVALID JSON: Duplicate keys");}
            }
            else if (c == '}'){
                objEndReached = true;
                break;
            }
            else{
                throw std::invalid_argument("INVALID JSON: Object/Start"); 
            }
        }
        else if (this->state == State::Colon){
            if (c == ':'){
                nextState();
            }
            else{
                throw std::invalid_argument("INVALID JSON: Object/Colon"); 
            }
        }
        else if (this->state == State::B4Val){
            val = HandlerHelper::handleAny(c);
        }
        else if (this->state == State::AfterVal){

            (*object)[key] = val;
            if (c == ','){
                nextState();
            }
            else if (c == '}'){
                objEndReached = true;
                break;
            }
            else {
                throw std::invalid_argument("INVALID JSON: Object/AfterVal"); 
            }
        }
        else if (this->state == State::AfterComma){
            if (c == '"'){
                // key = StringHandler::handle().value;
                // nextState();
                // if (object.find(key) != object.end()) {throw std::invalid_argument("INVALID JSON: Duplicate keys");}
            }
            else{
                throw std::invalid_argument("INVALID JSON: Object/AfterComma"); 
            }
        }
    }

    if (!objEndReached){
        throw std::invalid_argument("INVALID JSON: end of file reached before object end");
    }
    else {
        Json::JsonVal result; // what happens when fall out of scope?
        result.value = object; // What happens when fall out of scope?
        return result;
    }
}