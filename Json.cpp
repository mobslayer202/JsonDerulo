#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <stdexcept>

#include "Json.hpp"

Json::Json(const char* filePath){
    std::ifstream jsonFStream(filePath);
    std::string output;
    std::stack<DataType> typeStack;
    
    while (std::getline(jsonFStream, output)){
        
        for (std::string::iterator ch=output.begin(); ch!=output.end(); ch++){
            
            if (typeStack.empty()){ // If outside of any data type
                if (std::isspace(*ch)){
                    continue;
                }
                if (*ch == '-' or std::isdigit(*ch)){
                    typeStack.push(DataType::Number);
                    continue;
                }
                switch (*ch) {
                    case '{':
                        typeStack.push(DataType::Object);
                        break;
                    case '[':
                        typeStack.push(DataType::Array);
                        break;
                    case '"':
                        typeStack.push(DataType::String);
                        break;
                    case 't':
                        typeStack.push(DataType::True);
                        break;
                    case 'f':
                        typeStack.push(DataType::False);
                        break;
                    case 'n':
                        typeStack.push(DataType::Null);
                        break;
                    default:
                        throw std::invalid_argument("INVALID JSON"); // Can try defining own exception
                }
            }
            else if (typeStack.top() == DataType::Object){ // If inside Object
                
            }
            else if (typeStack.top() == DataType::Array){ // If inside Array
                
            }
            else if (typeStack.top() == DataType::String){ // If inside Array
                
            }
            else if (typeStack.top() == DataType::True){ // If inside Array
                
            }
            else if (typeStack.top() == DataType::False){ // If inside Array
                
            }
            else if (typeStack.top() == DataType::Null){ // If inside Array
                
            }
        }

    }
}