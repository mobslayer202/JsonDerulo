#pragma once

#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <fstream>
#include <stdexcept>

class Json{
    public:
        // Representation of JSON
        // - If not using Object or Array, no JsonVal in value
        // - Top level int,double,string will not be 
        struct JsonVal;
        // ^
        using jsonval = std::variant<std::shared_ptr<std::vector<JsonVal>>, 
            std::shared_ptr<std::unordered_map<std::string,JsonVal>>, 
            std::optional<bool>,
            double, 
            std::string>;
        // ^
        struct JsonVal {
            jsonval value;

            operator std::shared_ptr<std::vector<JsonVal>>(){ // Won't work with just vector for some reason

                return std::get<std::shared_ptr<std::vector<JsonVal>>>(value);
            }
            operator std::shared_ptr<std::unordered_map<std::string,JsonVal>>(){ // Won't work with just map for some reason

                return std::get<std::shared_ptr<std::unordered_map<std::string,JsonVal>>>(value);
            }
            operator std::optional<bool>(){ // find another way to represent null?
                
                return std::get<std::optional<bool>>(value);
            }
            operator double(){
                
                return std::get<double>(value);
            }
            operator std::string(){
                
                return std::get<std::string>(value);
            }
        };

        
        //Json();
        Json(const std::string& filePath);
        //void printFormatted();
        void makeFile(const std::string& filePath);
        //operator[]
        operator JsonVal(){
            return data;
        }
        

    private:
        JsonVal data;
};