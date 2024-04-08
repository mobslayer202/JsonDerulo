#include <fstream>
#include <iostream>
#include <string>

#include "CharReader.hpp"
// Static member must be defined outside of class
std::ifstream CharReader::jsonFStream; // Failed stream
std::string CharReader::buffer = "";
int CharReader::index = 0;

void CharReader::init(const char* filePath){
    CharReader::jsonFStream = std::ifstream(filePath);
    CharReader::buffer = "";
    CharReader::index = 0;
}

char CharReader::getNextChar(){

    if (buffer == "" or index == buffer.size()){
        std::cout << "\n";
        std::getline(jsonFStream, buffer);
        index = 0;
    }

    char x = buffer[index++];
    std::cout << x ;
    return buffer[index];
}

bool CharReader::canGet(){

    if (jsonFStream.eof() and index == buffer.size()){
        return false;
    }
    return true;
}

void CharReader::close(){ 
    jsonFStream.close();
}


char CharReader::seeNextChar(){
    if (index+1 == buffer.size()){ // Assumes not at last line
        char last = buffer[index];
        std::string temp;
        std::getline(jsonFStream, temp);

        std::cout << last << "XX\n";
        buffer = last + temp;
        index = 0;
    }

    return buffer[index+1];
}