#include <fstream>
#include <iostream>
#include <string>

#include "CharReader.hpp"
// Static member must be defined outside of class
std::ifstream CharReader::jsonFStream; // Failed stream
std::string CharReader::buffer = "";
int CharReader::index = 0;
bool CharReader::pastEnd = false;

void CharReader::init(const std::string& filePath){
    
    CharReader::jsonFStream = std::ifstream(filePath);
    CharReader::buffer = "";
    CharReader::index = 0;
    pastEnd = false;
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
        
        // If on last buffer and 
        // trying to increment to next char despite it being "" or last char
        //      mark that you are past end of file
        if (jsonFStream.eof()){
            pastEnd = true;
        }

        std::getline(jsonFStream, buffer);
        index = 0;
    }
    else{
        // Increment
        index++;
    }
}

bool CharReader::fileEnd(){

    // If on last buffer and last index of buffer
    return pastEnd;
}

