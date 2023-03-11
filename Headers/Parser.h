#include <map>
#include <string>
#include <vector>

class Parser {
    enum Tok_Ty {
        INT, FLOAT, VECTOR_INT, VECTOR_FLOAT, STRING
    };

    std::map<std::string, std::string>& variableMap;
    Parser(std::map<std::string, std::string>& variableMap): variableMap(variableMap) {};


    bool is_digit(char& c) { return c >= '0' && c <= '9'; };

    Tok_Ty identify_tok(std::string& tok);

    std::vector<int> get_int_vector(std::string& s);
    std::vector<double> get_float_vector(std::string& s);

};