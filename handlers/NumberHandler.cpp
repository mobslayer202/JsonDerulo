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
    double number = 0;

    bool numEndReached = false;
    while (CharReader::canGet()){

        char c = CharReader::
    }
}