//
//  ast.h
//  cpp
//
//  Created by Константин on 29.10.2019.
//  Copyright © 2019 Константин. All rights reserved.
//

#ifndef ast_h
#define ast_h

#include "Lexer.hpp"

enum AST_TYPES {NUMBER_NODE, VAR_NODE, BIN_OP_NODE};

class ExprNode {
public:
    const size_t type;
    ExprNode(size_t type) : type(type) {}
};

class NumberNode : public ExprNode {
public:
    const Token* number;
    NumberNode(Token* number) : ExprNode(NUMBER_NODE), number(number) {}
};

class VarNode : public ExprNode {
public:
    const Token* var;
    VarNode(Token* var) : ExprNode(VAR_NODE), var(var) {}
};

class BinOpNode : public ExprNode {
public:
    const Token* op;
    const ExprNode* left;
    const ExprNode* right;
    BinOpNode(Token* op, ExprNode* left, ExprNode* right): ExprNode(BIN_OP_NODE), op(op), left(left), right(right) {}
};

#endif /* ast_h */
