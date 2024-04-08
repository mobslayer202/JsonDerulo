#include "Json.hpp"

class NumberHandler{
    public:
        Json::JsonVal handle();

    private:
        // Start:
        //      -Accepts ('-', digit)
        // Normal:
        //      -Accepts (digit)
        // AfterNormal:
        //      -Accepts ('.', or anything) If anything, let parent handle it
        // AfterDecimal:
        //      -Accepts (digit, or anything) If anything, let parent handle it
        enum class State {Start, Normal, AfterNormal, AfterDecimal};
        State state = State::Start;
        void nextState();
};