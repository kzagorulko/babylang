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
                src += temp + '\n';
            }
        } else {
            std::cout << "File not found" << std::endl;
            return 4;
        }
    } else {
        src = ""; // write your code here
    }
    
    Lexer l(src);
    
    std::list<Token> tokens;
    
    try {
        tokens = l.lex();
    } catch (std::tuple<char const*, char const*, std::pair<int, int>> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n";
        std::cout << "In function " << std::get<1>(e) << " was thrown `" << std::get<0>(e) << "` at "
                  << "position " + std::to_string(std::get<2>(e).first) + " row " + std::to_string(std::get<2>(e).second) + " symbol"
                  << std::endl ;
    }
    
    Parser p(tokens);
    std::list<Block*> blocks;
    
    try {
        blocks = p.parse_blocks();
    } catch (std::tuple<char const*, char const*, std::pair<int, int>> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n";
        std::cout << "In function " << std::get<1>(e) << " was thrown `" << std::get<0>(e) << "` at "
                  << "position " + std::to_string(std::get<2>(e).first) + " row " + std::to_string(std::get<2>(e).second) + " symbol"
                  << std::endl ;
        return 1;
    } catch (std::tuple<std::string, char const*, std::pair<int, int>> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n";
        std::cout << "In function " << std::get<1>(e) << " was thrown `" << std::get<0>(e) << "` at "
                  << "position " + std::to_string(std::get<2>(e).first) + " row " + std::to_string(std::get<2>(e).second) + " symbol"
                  << std::endl ;
    }
    
    try {
        std::map<std::string, float> values;
        Parser::run(blocks, values);
    } catch (std::pair<char const*, char const*> e) {
        std::cout << std::endl << std::endl << "\033[1;31m---Runtime exception---\033[0m\n"
                  << "In function " << e.second << " was thrown `" << e.first << "`" << std::endl;
        return 2;
    }
    
    return 0;
}


