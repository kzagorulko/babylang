//
//  Lexer.hpp
//  Header with lexer for project.
//
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <regex>
#include <list>

#define TOKEN_TYPES \
X(NUMBER,       "NUMBER",       "[-+]?[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?") \
X(PRINT,        "PRINT",        "print") \
X(IF,           "IF",           "if") \
X(THEN,         "THEN",         "then") \
X(ELSE,         "ELSE",         "else") \
X(END,          "END",          "end") \
X(ID,           "ID",           "[a-zA-Z_][a-zA-Z_0-9]*") \
X(ADD,          "ADD",          "\\+") \
X(SUB,          "SUB",          "-") \
X(MUL,          "MUL",          "\\*") \
X(DIV,          "DIV",          "/") \
X(LPAR,         "LPAR",         "\\(") \
X(RPAR,         "RPAR",         "\\)") \
X(SPACE,        "SPACE",        "[ \t\r;]+") \
X(MORE,         "MORE",         ">") \
X(LESS,         "LESS",         "<") \
X(NEXT_LINE,    "NEXT_LINE",    "[\n]") \
X(EQUAL,        "EQUAL",        "=")



#define X(type, strType, regex) regex,
static char const *TOKEN_REGEX[] = { TOKEN_TYPES };
#undef X

#define X(type, strType, regex) strType,
static char const *TOKEN_NAME[] = { TOKEN_TYPES };
#undef X

#define X(type, strType, regex) type,

enum TOKEN_TYPE : size_t {
    TOKEN_TYPES
};

static size_t const ITERIBLE_TOKEN_TYPES[] = { TOKEN_TYPES };
#undef X



class Token {
public:
    const size_t type; // TOKEN_TYPE ENUM
    const std::string text;
    const std::pair<int, int> pos_in_text;
    Token(size_t type, std::string text, std::pair<int, int> pos_in_text) : type(type), text(text), pos_in_text(pos_in_text) {};
    friend std::ostream& operator<<(std::ostream &out, const Token& t);
};



class Lexer {
private:
    std::string src;
    int pos;
    int row;
    int symbol;
    std::list<Token> tokens;
    std::pair<int, int> get_position(std::list<int> location);
    
public:
    Lexer(std::string src): src(src), pos(0), row(1), symbol(1) {}
    std::list<Token> lex();
    
};

#endif /* Lexer_hpp */
