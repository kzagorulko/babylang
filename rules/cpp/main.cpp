#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <map>

#include "Lexer.hpp"
#include "Parser.hpp"


int main(int argc, const char * argv[]) {
    
    std::string src = "((2 * 1) = 2)";
    Lexer l(src);
    
    std::list<Token> tokens = l.lex();    
    
    Parser p(tokens);
    ExprNode* node;
    
    try {
        node = p.parse_expression();
    } catch (std::tuple<char const*, char const*, int> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n";
        std::cout << "In function " << std::get<1>(e) << " was thrown `" << std::get<0>(e) << "` at "
                  << (std::get<2>(e) < tokens.size() ? "position " + std::to_string(std::get<2>(e)) : "the end of file")
                  << std::endl ;
        return 1;
    }
    
    int result;
    
    try {
        result = Parser::eval(node);
    } catch (std::pair<char const*, char const*> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n"
                  << "In function " << e.second << " was thrown `" << e.first << "`" << std::endl;
        return 2;
    }
    
    std::cout << "Answer: " << result << std::endl;
    
    return 0;
}


