
class CharReader{
    public:
        //~CharReader();
        // To be called at start of json, top level nesting of json file
        static void init(const char* filePath);
        static char getNextChar();
        static bool canGet(); // MUST be called before getNextChar
        static void close();

    private:
        static std::ifstream jsonFStream;
        static std::string buffer;
        static int index;
};