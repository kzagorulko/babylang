//
//  Parser.cpp
//  cpp
//
//  Created by Константин on 29.10.2019.
//  Copyright © 2019 Константин. All rights reserved.
//

#include "Parser.hpp"

Parser::Parser(std::list<Token> tokens): pos(0) {
    for (Token t:tokens) {
        if (t.type != SPACE) {
            this->tokens.push_back(Token(t.type, t.text, t.pos));
        }
    }
}

void Parser::error(std::string message) {
    if (pos < tokens.size()) {
        std::list<Token>::iterator it = tokens.begin();
        std::advance(it, pos);
        std::string m, f_message = message + " at position " + std::to_string(it->pos);
        m = f_message;
        throw m;
    } else {
        throw message + " at the end of file";
    }
}

Token* Parser::match(std::set<size_t> types) {
    if (pos < tokens.size()) {
        std::list<Token>::iterator it = tokens.begin();
        std::advance(it, pos);
        if (types.count(it->type) > 0) {
            pos++;
            return &*it;
        }
    }
    return nullptr;
}

Token* Parser::match(size_t type) {
    if (pos < tokens.size()) {
        std::list<Token>::iterator it = tokens.begin();
        std::advance(it, pos);
        if (it->type == type) {
            pos++;
            return &*it;
        }
    }
    return nullptr;
}

Token Parser::require(size_t type) {
    Token* t = match(type);
    if (t == nullptr) {
        error("Expected " + std::string(TOKEN_NAME[type]));
    }
    return *t;
}

ExprNode* Parser::parse_elem() {
    Token* num = match(NUMBER);
    if (num != nullptr) {
        return new NumberNode(num);
    }
    Token* id = match(ID);
    if (id != nullptr) {
        return new VarNode(id);
    }
    error("Expected number or variable");
    return nullptr;
}

ExprNode* Parser::parse_bracketed() {
    if (match(LPAR) != nullptr) {
        ExprNode* e = parse_expression();
        require(RPAR);
        return e;
    }
    return parse_elem();
}

ExprNode* Parser::parse_summand() {
    ExprNode* e1 = parse_bracketed();
    Token* op;
    std::set<size_t> types {MUL, DIV};
    
    while ((op = match(types)) != nullptr) {
        ExprNode* e2 = parse_bracketed();
        e1 = new BinOpNode(op, e1, e2);
    }
    return e1;
}

ExprNode* Parser::parse_expression() {
    ExprNode* e1 = parse_summand();
    Token* op;
    std::set<size_t> types {ADD, SUB};
    
    while ((op = match(types)) != nullptr) {
        ExprNode* e2 = parse_summand();
        e1 = new BinOpNode(op, e1, e2);
    }
    return e1;
}

int Parser::eval(ExprNode* node) {
    switch (node->type) {
        case NUMBER_NODE:
            return std::stoi((((NumberNode*) node)->number)->text);
            break;
        case BIN_OP_NODE:
        {
                BinOpNode bon = *((BinOpNode*) node);
                int l = eval((ExprNode *) bon.left);
                int r = eval((ExprNode *) bon.right);
                switch (bon.op->type) {
                    case ADD: return l + r;
                    case SUB: return l - r;
                    case MUL: return l * r;
                    case DIV: return l / r;
                }
        }
            break;
            
        case VAR_NODE:
        {
            int value;
            VarNode vn = *((VarNode*) node);
            std::cout << "Enter value " << vn.var->text << ": ";
            std::cin >> value;
            return value;
        }
            break;
            
        default:
            throw "IllegalStateException";
            break;
    }
    
    return 69;
}
