#include "../Headers/Lexer.h"

// #define DEBUG



Lexer::Token_Ty Lexer::get_tok()
{
    while (is_space(c))
        c = configFile->get();

    token = "";
    int n = 1000;

    while (!is_token_terminator(c) && n-- > 0)
    {
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

Lexer::ReadLine_Ty Lexer::readFile()
{
    Token_Ty get_tok_ret = get_tok();
    std::string varString, valueString;
    while (get_tok_ret != EOF_FAILURE)
    {
        if (get_tok_ret != VARIABLE_SUCCESS)
        {
            __PRINT_ERR("Expected token to be variable")
            return READLINE_FAILURE;
        }
        varString = token;
        c = configFile->get(); // consume the =
        get_tok_ret = get_tok();
        if (get_tok_ret != VALUE_SUCCESS)
        {
            __PRINT_ERR("Expected token to be Value")
            return READLINE_FAILURE;
        }
        valueString = token;
        valuesMap[varString] = valueString;
        if (c != ';')
        {
            __PRINT_ERR("Expected ';'");
            return READLINE_FAILURE;
        }
        c = configFile->get(); // consume the ;
        valuesMap[varString] = valueString;
        get_tok_ret = get_tok();
    }
    return READLINE_SUCCESS;
}

#ifdef DEBUG
int main()
{
    std::fstream configFile;
    const char *fileName = "/home/hhn/cs/PC03-NSS/.env";
    configFile.open(fileName);
    Lexer lexy(&configFile);
    lexy.readFile();
    std::cout << lexy.valuesMap["a"] << std::endl;
    std::cout << lexy.valuesMap["p"] << std::endl;
    std::cout << lexy.valuesMap["r"] << std::endl;
    return 0;
}
#endif