#include "../Headers/Parser.h"

std::vector<double> Parser::get_float_vector(std::string& s) {
    std::vector<double> v;
    std::string tok;
    int i = 0;
    char c;
    do {
        char c = s[i];
        if (c == ',') {
            v.push_back(stod(tok));
            tok = "";
            continue;
        }
        tok += c;
    } while (++i < s.size());
    v.push_back(stod(tok));
    return v;
}

std::vector<int> Parser::get_int_vector(std::string& s) {
    std::vector<int> v;
    std::string tok;
    int i = 0;
    char c;
    do {
        char c = s[i];
        if (c == ',') {
            v.push_back(stoi(tok));
            tok = "";
            continue;
        }
        tok += c;
    } while (++i < s.size());
    v.push_back(stoi(tok));
    return v;
}

Parser::Tok_Ty Parser::identify_tok(std::string& tok) {
    bool isVector = false;
    Tok_Ty ty = INT;
    int i = 0;
    char c;
    do {
        char c = tok[i];
        if (c == ',') {
            isVector = true;
            continue;
        }
        if (!(c == '.' || is_digit(c)))
            return STRING;
        if (c == '.')
            ty = FLOAT;
    } while (++i < tok.size());
    if (isVector)
        ty = (Tok_Ty)(ty + 2); // returns corresponding float
    return ty;
}