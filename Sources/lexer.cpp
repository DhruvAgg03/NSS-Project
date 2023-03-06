#include "../Headers/Lexer.h"

#define DEBUG

#ifdef DEBUG
#define __PRINT_ERR(s) std::cout << "ERROR : " << s << '\n';
#else   
#define __PRINT_ERR(s) 
#endif


class Lexer {
    enum Token_Ty {
        VARIABLE_SUCCESS,
        VALUE_SUCCESS,
        EOF_FAILURE,
        LONG_TOK_FAILURE,

    };

    enum ReadLine_Ty {
        READLINE_SUCCESS,
        READLINE_FAILURE
    };

    typedef struct Value_Ty {

    } value;

    char c = 0;
    std::string token = "";
    std::fstream* configFile;

    std::map<std::string, value> valuesMap;

    static inline bool is_token_terminator(char c) {
        return (c == '=' || c == ';' || c == EOF);
    }

    static inline bool is_space(char c) {
        return (c == ' ' || c == '\n' || c == '\t');
    }

public:
    Lexer(std::fstream* configFile): configFile(configFile) {}

    Token_Ty  get_tok() {
        while (is_space(c))
            c = configFile->get();

        token = "";
        int n = 100;

        while (!is_token_terminator(c) && n > 0) {
            token = token + c;
            c = configFile->get();
        }

        if (c == '=')
            return VARIABLE_SUCCESS;
        else if (c == ';')
            return VALUE_SUCCESS;
        else if (c == EOF)
            return EOF_FAILURE;
        return LONG_TOK_FAILURE;
    }

    ReadLine_Ty readLine() {
        Token_Ty get_tok_ret = get_tok();
        std::string varString, valueString;
        while (get_tok_ret != EOF_FAILURE) {
            if (get_tok_ret != VARIABLE_SUCCESS) {
                __PRINT_ERR("Expected token to be variable")
                    return READLINE_FAILURE;
            }
            varString = token;
            get_tok_ret = get_tok();
            if (get_tok_ret != VALUE_SUCCESS) {
                return READLINE_FAILURE;
            }
            valueString = token;
        }

    }

};