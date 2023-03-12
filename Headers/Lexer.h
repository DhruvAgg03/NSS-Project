#include <map>
#include <string>
#include <fstream>
#include <iostream>

#ifdef DEBUG
#define __PRINT_ERR(s) std::cout << "ERROR : " << s << '\n';
#else
#define __PRINT_ERR(s)
#endif

class Lexer
{
public:
    enum Token_Ty
    {
        VARIABLE_SUCCESS,
        VALUE_SUCCESS,
        EOF_FAILURE,
        LONG_TOK_FAILURE,

    };

    enum ReadLine_Ty
    {
        READLINE_SUCCESS,
        READLINE_FAILURE
    };

    char c = 0;
    std::string token = "";
    std::fstream *configFile;

    static inline bool is_token_terminator(char c) { return (c == '=' || c == ';' || c == EOF); }

    static inline bool is_space(char c) { return (c == ' ' || c == '\n' || c == '\t' || c == '\0'); }

    std::map<std::string, std::string> valuesMap;

    Lexer(std::fstream *configFile) : configFile(configFile) {}

    Token_Ty get_tok();
    ReadLine_Ty readFile();
};