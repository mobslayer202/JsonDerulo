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

void CharReader::close(){ 

    jsonFStream.close();
}

char CharReader::getChar(){
    return buffer[index];
}

void CharReader::increment(){

    // If just started or at last index of buffer, refresh buffer with new data
    // Put index at the start of new data
    if (buffer == "" or index == buffer.size()-1){
        std::getline(jsonFStream, buffer);
        index = 0;
    }
    else{
        // Increment
        index++;
    }
}

bool CharReader::fileEnd(){

    // If on last buffer and index out of bounds
    if (jsonFStream.eof() and index == buffer.size()){
        return true;
    }
    return false;
}

