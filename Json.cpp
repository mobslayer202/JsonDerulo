#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>

#include "Json.hpp"

Json::Json(const char* filePath){
    std::ifstream jsonFStream(filePath);
    std::string output;
    std::stack<char> openClose;
    bool inString = false;
    
    while (std::getline(jsonFStream, output)){
        
        for (std::string::iterator ch=output.begin(); ch!=output.end(); ch++){
            
            if (!inString){ // We are not in a string
                if (std::isspace(*ch)){
                    continue;
                }
                if (*ch == '"'){
                    inString = true;
                }
                else if (*ch == '[' or *ch == '{'){
                    openClose.push(*ch);
                }
                else if (*ch == ']' or *ch == '}'){
                    if(*ch != openClose.top()){
                        std::cout << "YOU MESSED UP!!!\n";
                    }
                }
            }
        }

    }
}