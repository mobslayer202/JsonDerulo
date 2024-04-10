#include "Json.hpp"

class HandlerHelper{

    public:
        // Called ONLY in top level, object value, array element
        static Json::JsonVal handleAny(char c);
        //static Json::JsonVal convertJsonVal();
};