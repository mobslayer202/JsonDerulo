#include "Json.hpp"

class ArrayHandler{
    public:
        std::shared_ptr<std::vector<Json::JsonVal>> handle();

    private:
        // Start:
        //      - Accepts (']', any data type)
        // AfterElement:
        //      - Accepts (']', ',')
        // AfterComma
        //      - Accepts (any data type)
        enum class State {Start, AfterElement, AfterComma};
        State state = State::Start;
        void nextState();
};