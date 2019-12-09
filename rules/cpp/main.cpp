#include <map>
#include <list>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>

#include "Lexer.hpp"
#include "Parser.hpp"


int main(int argc, const char * argv[]) {
    
    std::string src = "";
    
    if (argc > 1) {
        std::ifstream in(argv[1]);
        
        if (in.is_open()) {
            std::string temp;
            while (std::getline(in, temp)) {
                src += temp;
            }
        } else {
            std::cout << "File not found" << std::endl;
            return 4;
        }
    } else {
        src = "end; then print 32; else  print 2; end; print 3; print 4; print 5;";
    }
    
    Lexer l(src);
    
    std::list<Token> tokens = l.lex();
    
    Parser p(tokens);
    std::list<Block*> blocks;
    
    try {
        blocks = p.parse_blocks();
    } catch (std::tuple<char const*, char const*, int> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n";
        std::cout << "In function " << std::get<1>(e) << " was thrown `" << std::get<0>(e) << "` at "
                  << (std::get<2>(e) < tokens.size() ? "position " + std::to_string(std::get<2>(e)) : "the end of file")
                  << std::endl ;
        return 1;
    } catch (std::tuple<std::string, char const*, int> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n";
        std::cout << "In function " << std::get<1>(e) << " was thrown `" << std::get<0>(e) << "` at "
                  << (std::get<2>(e) < tokens.size() ? "position " + std::to_string(std::get<2>(e)) : "the end of file")
                  << std::endl ;
    }
    
    try {
        Parser::run(blocks);
    } catch (std::pair<char const*, char const*> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n"
                  << "In function " << e.second << " was thrown `" << e.first << "`" << std::endl;
        return 2;
    }
    
    return 0;
}


