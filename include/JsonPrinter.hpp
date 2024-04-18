#pragma once

#include <fstream>

#include "Json.hpp"

class JsonPrinter{

    public:
        JsonPrinter(std::string filePath);
        void printJson(Json::JsonVal root, int tabLevel);

    private:
        std::ofstream output;
        void indent(int tabLevel);
        bool oneRowArr(std::vector<Json::JsonVal> array);
};