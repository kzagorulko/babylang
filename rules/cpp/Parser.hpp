//
//  Parser.hpp
//  cpp
//
//  Created by Константин on 29.10.2019.
//  Copyright © 2019 Константин. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <set>
#include <list>

#include <stdio.h>

#include "ast.h"
#include "Utils.hpp"
#include "Lexer.hpp"

enum State { S_0, S_FINAL, S_LOOP };

class Parser {
private:
    int pos;
    std::list<Token> tokens;
    
    Token* match(std::set<size_t> types);
    Token* match(size_t type);
    Token require(size_t type);
    ExprNode* parse_elem();
    ExprNode* parse_logical();
    ExprNode* parse_summand();
    ExprNode* parse_bracketed();
public:
    Parser(std::list<Token> tokens);
    ExprNode* parse_expression();
    std::list<Block*> parse_blocks(int level=0);
    static int eval(ExprNode* node);
    static void run(std::list<Block*> blocks);
};

#include <stdio.h>

#endif /* Parser_hpp */
