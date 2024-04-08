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
        //      -Accepts ('.', ) // Need to peek
        // AfterDecimal:
        //      -Accepts (digit)
        enum class State {Start, Normal, AfterNormal, AfterDecimal};
};