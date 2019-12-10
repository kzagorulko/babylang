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

enum AST_TYPES {NUMBER_NODE, VAR_NODE, BIN_OP_NODE, IF_BLOCK, PRINT_BLOCK};

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

// Blocks

class Block {
public:
    const size_t type;
    Block(size_t type): type(type) {}
};

class IfBlock : public Block {
public:
    const ExprNode* condition;
    const std::list<Block*> then_block;
    const std::list<Block*> else_block;
    IfBlock(ExprNode* condition, std::list<Block*> then_block, std::list<Block*> else_block): Block(IF_BLOCK), condition(condition), then_block(then_block), else_block(else_block) {}
};

class PrintBlock : public Block {
public:
    const ExprNode* value;
    PrintBlock(ExprNode* value): Block(PRINT_BLOCK), value(value) {}
};

#endif /* ast_h */
