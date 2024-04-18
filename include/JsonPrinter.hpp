#pragma once

#include <fstream>

#include "Json.hpp"

#define JSONVAL_ARR std::shared_ptr<std::vector<JsonVal>>
#define JSONVAL_OBJ std::shared_ptr<std::unordered_map<std::string, JsonVal>>



class JsonPrinter{

    public:
        JsonPrinter(std::string filePath);
        void printJson(Json::JsonVal root, int tabLevel);

    private:
        std::ofstream output;
        void indent(int tabLevel);
        bool oneRowArr(std::vector<Json::JsonVal> array);
};