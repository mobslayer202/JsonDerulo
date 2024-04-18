#include "JsonPrinter.hpp"

JsonPrinter::JsonPrinter(std::string filePath){
    this->output = std::ofstream(filePath);
}

void JsonPrinter::printJson(Json::JsonVal root, int tabLevel){
    // object
    if (auto value = std::get_if<std::shared_ptr<std::unordered_map<std::string, Json::JsonVal>>>(&root.value)){ // Needs an address and not value?
        this->output << "{\n";
        indent(tabLevel+1);

        // Right before first key,value pair printed
        bool first = true;
        for (const auto& [skey, jVal] : **value){ 
            if (!first){
                this->output << ",\n";
                indent(tabLevel+1);
            }
            else{
                first = false;
            }
            this->output << '"' << skey << "\" : ";
            printJson(jVal, tabLevel+1);
        }
        // Right after last key,value pair printed

        this->output << "\n";
        indent(tabLevel);
        this->output << "}";
    }
    // array
    else if (auto value = std::get_if<std::shared_ptr<std::vector<Json::JsonVal>>>(&root.value)){ // Needs an address and not value?
        this->output << "[\n";
        indent(tabLevel+1);
        // Right before printing first element
        if (oneRowArr(**value)){ // Address of shared_ptr of vector
            bool first = true;
            for (const Json::JsonVal& jVal : **value){ 
                if (!first){
                    this->output << ", ";
                }
                else{
                    first = false;
                }
                printJson(jVal, 0);
            }
        }
        else{
            bool first = true;
            for (const Json::JsonVal& jVal : **value){ 
                if (!first){
                    this->output << ",\n";
                    indent(tabLevel+1);
                }
                else{
                    first = false;
                }
                printJson(jVal, tabLevel+1);
            }
        }
        // Right after last element is printed
        this->output << "\n";
        indent(tabLevel);
        this->output << "]";
    }
    // bool or null
    else if (auto value = std::get_if<std::optional<bool>>(&root.value)){
        if (!value->has_value()){ // value is a pointer?
            this->output << "null";
        }
        else if (*value){
            this->output << "true";
        }
        else{
            this->output << "false";
        }
    }
    // string
    else if (auto value = std::get_if<std::string>(&root.value)){
        this->output << '"' << *value << '"';
    }
    // double
    else if (auto value = std::get_if<double>(&root.value)){
        this->output << *value;
    }
}

void JsonPrinter::indent(int tabLevel){
    for (int i=0; i<tabLevel; i++){
        this->output << "  ";
    }
}

bool JsonPrinter::oneRowArr(std::vector<Json::JsonVal> array){

    for (const Json::JsonVal& jVal : array){ // reference instead of copy?
        if(auto value = std::get_if<std::shared_ptr<std::vector<Json::JsonVal>>>(&jVal.value)){ // Can shorten?
            return false;
        }
        else if(auto value = std::get_if<std::shared_ptr<std::unordered_map<std::string, Json::JsonVal>>>(&jVal.value)){ // Can shorten?
            return false;
        }
    }
    return true;
}