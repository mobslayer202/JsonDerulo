
class CharReader{
    public:

        // To be called at start of json, top level nesting of json file
        static void init(const char* filePath);
        static void close();
        static char getChar();
        static void increment();

        // If true:
        //      - no point in getChar() -> index out of bounds
        //      - no point in increment() -> no more fresh buffers of data
        static bool fileEnd();  

    private:
        static std::ifstream jsonFStream;
        static std::string buffer;
        static int index;
};