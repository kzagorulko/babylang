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
X(NUMBER,   "NUMBER",   "[1-9][0-9]*") \
X(ID,       "ID",       "[a-zA-Z_][a-zA-Z_0-9]*") \
X(ADD,      "ADD",      "\\+") \
X(SUB,      "SUB",      "-") \
X(MUL,      "MUL",      "\\*") \
X(DIV,      "DIV",      "/") \
X(LPAR,     "LPAR",     "\\(") \
X(RPAR,     "RPAR",     "\\)") \
X(SPACE,    "SPACE",    "[ \t\r\n]+")

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
private:
    size_t type; // TOKEN_TYPE ENUM
    std::string text;
    int index;

public:

    Token(size_t type, std::string text, int index);
    friend std::ostream& operator<<(std::ostream &out, const Token& t);
};



class Lexer {
private:
    std::string src;
    int pos;
    std::list<Token> tokens;
    
public:
    Lexer(std::string src);
    std::list<Token> lex();
    
};

#endif /* Lexer_hpp */