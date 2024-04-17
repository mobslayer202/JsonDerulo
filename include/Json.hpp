#pragma once

#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class Json{
    public:
        // Representation of JSON
        // - If not using Object or Array, no JsonVal in value
        // - Top level int,double,string will not be 
        struct JsonVal;
        // ^
        using jsonval = std::variant<std::shared_ptr<std::vector<JsonVal>>, 
            std::shared_ptr<std::unordered_map<std::string,JsonVal>>, 
            bool,
            double, 
            std::string>;
        // ^
        struct JsonVal {
            jsonval value;
        };

        
        //Json();
        Json(const char* filePath);
        //void printFormatted();
        void makeFile(const char* filePath);
        //operator[]

        

    private:
        JsonVal data;

};