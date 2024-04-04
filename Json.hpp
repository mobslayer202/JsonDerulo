#include <variant>
#include <unordered_map>
#include <vector>

class Json{
    public:
        //std::variant<std::vector, 
        //Json();
        Json(const char* filePath);
        void printFormatted();
        //void makeFile(const char* filePath);
        //operator[]
};