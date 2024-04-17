#pragma once

class CharReader{
    public:

        // To be called at start of json, top level nesting of json file
        static void init(const char* filePath);
        static void close();
        static char getChar(); // return char at current index
        static void increment(); // Increment index to location of next valid char

        // If true:
        //      - no point in getChar() -> looking past the last char of file
        //      - no point in increment() -> no more fresh buffers of data
        static bool fileEnd();  

    private:
        static std::ifstream jsonFStream;
        static std::string buffer; // Buffer to store lines of the json data
        static int index; // Index for current char
        static bool pastEnd; // Indicates if you are past the last char
};