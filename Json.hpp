#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class Json{
    public:
        // Representation of JSON
        // - If not using Object or Array, no JsonVal in value
        // - Top level int,double,string will not be 
        struct JsonVal;
        // ^
        using jsonval = std::variant<std::shared_ptr<std::vector<JsonVal>>, 
            std::shared_ptr<std::unordered_map<std::string,JsonVal>>, 
            bool,
            double, 
            std::string>;
        // ^
        struct JsonVal {
            jsonval value;
        };

        //Json();

        // Tasks -----------------------------------------
        // - Detect Valid Json
        //      - valid data types in json
        //          #1 double (no int -GPT, can be negative, can have e or E), string, bool, null, array, object
        //          #2 only strings can be keys of object
        //      - string format
        //          #3 strings have double quotes around
        //          4 no numbers at start of string
        //          5 "special characters" are excaped
        //      - valid [] and {} positions
        //          #6 every open must close
        //      #7 commas separate elements in [] and {}
        // - Parse Json
        // ------------------------------------------------
        // Implementation --------------------------------
        // - Rules: Tasks (1,2,3,6,7) - Disregard (e or E for numbers, 5: special char in string, 4: numbers at start of string)
        //
        // Go through all non whitespace character left to right, top to bottom:
        //      If [ or {: after dealt with inside, must see matching ] or }
        //      If -: must be followed by number OR must be wrapped in ""
        //      If number: must be outside object/array OR must be object value OR must be array element
        //      If " : must see matching "  after characters inside
        //      If , : must be inside object or array, must be between data types (before: ", -, number, [, { )
        //      If ':' : must be after string, before data type
        //      If other char: must be true or false OR be string (within "")
        //
        // Observation
        //      "Go Through" rules dont apply when char wrapped in ""
        //      Should also account for 
        Json(const char* filePath);
        //void printFormatted();
        //void makeFile(const char* filePath);
        //operator[]

    private:
        enum class DataType {Object, Array, String, Number, True, False, Null};

};