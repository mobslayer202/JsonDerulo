#pragma once

#include "Json.hpp"

class ObjectHandler{
    public:
        std::shared_ptr<std::unordered_map<std::string, Json::JsonVal>> handle();
    
    private:
        // States and acceptance:
        //  ALL STATES ACCEPT WHITESPACE
        // Start: reading first char after '{' 
        //      - Accepts ( '}', '"' )
        // Colon: reading first char after StringHandler finishes 
        //      - Accepts (':')
        // B4Val: reading first char after ':'
        //      - Accepts any data type start char
        // AfterVal: reading first char after Data Type Handler finishes
        //      - Accepts (',', '}')
        // AfterComma: reading first char after ','
        //      - Accepts ('"')
        enum class State{Start, Colon, B4Val, AfterVal, AfterComma};
        State state = State::Start;
        void nextState(); // operator++ need friend function and not semantic
        
};