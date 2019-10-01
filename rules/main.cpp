#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <map>

#include "Lexer.hpp"


int main(int argc, const char * argv[]) {
    
    std::string src = "x + 5 * 2001 - (12 + 1)";
    Lexer l(src);
    
    std::list<Token> tlist = l.lex();
    
    for (Token t: tlist) {
        std::cout << t;
    }
    
    return 0;
}


