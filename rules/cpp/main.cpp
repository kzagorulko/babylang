#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <map>

#include "Lexer.hpp"
#include "Parser.hpp"


int main(int argc, const char * argv[]) {
    
    std::string src = "x + 5 * 2001 - (12 + 1)";
    Lexer l(src);
    
    std::list<Token> tokens = l.lex();
    
    Parser p(tokens);
    ExprNode* node = p.parse_expression();

    int result = Parser::eval(node);
    std::cout << "Answer: " << result << std::endl;
    
    return 0;
}


