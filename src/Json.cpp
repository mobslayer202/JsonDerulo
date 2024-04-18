#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <stdexcept>
//#include <option>

#include "Json.hpp"
#include "HandlerHelper.hpp"
#include "CharReader.hpp"
#include "RunSettings.hpp"

Json::Json(const char* filePath){

    JLOG("Json Constructor: Starting Parse")
    CharReader::init(filePath);
    CharReader::increment(); // Put real data in buffer
    char c = CharReader::getChar(); // Breaks on empty file
    this->data = HandlerHelper::handleAny(c);
    JLOG("Json Constructor: Parse Completed!")
}

void Json::makeFile(const char* filePath){
    //std::ofstream output("JsonExamples/result.json");
    /*auto jsonArr = std::get<std::shared_ptr<std::vector<JsonVal>>>(data.value);
    auto a = std::get<std::string>((*jsonArr)[0].value);
    auto b = std::get<double>((*jsonArr)[1].value);
    auto c = std::get<std::string>((*jsonArr)[2].value);
    auto d = std::get<double>((*jsonArr)[3].value);
    auto e = std::get<std::string>((*jsonArr)[4].value);
    auto f = std::get<double>((*jsonArr)[5].value);
    auto g = std::get<double>((*jsonArr)[6].value);
    auto h = std::get<std::string>((*jsonArr)[7].value);
    std::cout << a << "\n" << b << "\n" << c << "\n" << d << "\n" << e << "\n" << f << "\n" << g << "\n" << h << "\n";*/

    auto jsonMap = std::get<std::shared_ptr<std::unordered_map<std::string, JsonVal>>>(data.value);
    auto a = (*jsonMap)["employee"];

    auto jsonMap2 = std::get<std::shared_ptr<std::unordered_map<std::string, JsonVal>>>(a.value);
    auto b = (*jsonMap2)["name"];

    auto c = std::get<std::string>(b.value);
    std::cout << c << "\n";

    auto d = (*jsonMap2)["salary"];

    auto e = std::get<double>(d.value);
    std::cout << e << "\n";

    auto f = (*jsonMap2)["married"];

    auto g = std::get<std::optional<bool>>(f.value);
    std::cout << g.value() << "\n";

}