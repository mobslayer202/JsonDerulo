
class CharReader{
    public:
        //~CharReader();
        // To be called at start of json, top level nesting of json file
        static void init(const char* filePath);
        static char getNextChar(); // Change name or split increment and get? This one nice though
        static bool canGet(); // MUST be called before getNextChar
        static void close();

        // For Number Handler
        static bool endOfLine(); // Called before seeNext() in Number Handler - There is no newline inside a number
        static char seeNext(); // This one also kind of getNext() :(

    private:
        static std::ifstream jsonFStream;
        static std::string buffer;
        static int index;
};