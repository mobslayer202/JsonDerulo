#include <Json.hpp>
class ObjectHandler{
    public:
        ObjectHandler();
        std::unordered_map<std::string,Json::JsonVal> Handle();
    
    private:
        enum class State{Start, Colon, B4Val, AfterVal, AfterComma};
        
};