#pragma once

#include "Json.hpp"

class NumberHandler{
    public:
        double handle();

    private:
        // Start:
        //      -Accepts ('-', digit)
        // Normal:
        //      -Accepts (digit)
        // AfterDecimal:
        //      -Accepts (digit, or anything) If anything, let parent handle it
        enum class State {Start, Normal, AfterDecimal};
        State state = State::Start;
        void nextState();
};