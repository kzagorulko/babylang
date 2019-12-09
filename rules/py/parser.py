"""
Parser which works with tokens
"""
from lexer import Lexer, TokenType


class Parser:

    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

    def match(self, expectedTypes):
        if self.pos < len(self.tokens):
            token = self.tokens[self.pos]
            if token.type in expectedTypes:
                self.pos += 1
                return True

        return False


    def expr(self):
        e1 = self.slag()
        while self.match([TokenType.ADD, TokenType.SUB]):
            op = self.tokens[self.pos-1]
            e2 = self.slag()
            e1 = BimOpNode(op.text, e1, e2)

        return e1

    def logic_expr(self):
        e1 = self.expr()
        while self.match([TokenType.MORE, TokenType.LESS, TokenType.EMORE, TokenType.ELESS]):
            op = self.tokens[self.pos-1]
            e2 = self.expr()
            e1 = BimOpNode(op.text, e1, e2)

        return e1


    def mnog(self):
        if self.match([TokenType.LPAR]):
            e = self.expr()
            self.require(TokenType.RPAR)
            return e
        else:
            e = self.require(TokenType.NUMBER)
            e = NumberNode(e.text)
            return e


    def slag(self):
        e1 = self.mnog()
        while self.match([TokenType.MUL, TokenType.DIV]):
            op = self.tokens[self.pos-1]
            e2 = self.mnog()

            e1 = BimOpNode(op.text, e1, e2)

        return e1

    def elem(self):
        if self.match([TokenType.NUMBER]):
            return NumberNode(self.tokens[self.pos])
        if self.match([TokenType.ID]):
            return VarNode(self.tokens[self.pos])
        self.error("Ожидалось число или ID")


    def eval(self, n):
        if type(n) is NumberNode:
            return int(n.number)
        if type(n) is BimOpNode:
            l = self.eval(n.left)
            r = self.eval(n.right)

            if n.op == '+':
                return l+r
            elif n.op == '*':
                return l*r
            elif n.op == '-':
                return l-r
            elif n.op == '/':
                return l/r
            elif n.op == '>':
                return l>r
            elif n.op == '<':
                return l<r
            elif n.op == '>=':
                return l>=r
            elif n.op == '<=':
                return l<=r

    def require(self, expected):
        if not self.match([expected]):
            self.error("Ожидалось " + expected.value[0] + " " + self.tokens[self.pos].text)
        return self.tokens[self.pos-1]

    def error(self, msg):
        raise Exception("{} at {}".format(msg, self.pos))

# построение AST
# x+2*y
#     +
#  x     *
#       2  y
# Типы узлов:
# 1. лист, число
# 2. лист, ид
# 3. бинарная оп

# expression problem (представление дерева в языке)

class NumberNode:
    #number;
    def __init__(self, number):
        self.number = number

class VarNode:
    #id
    def __init__(self, var):
        self.var = var

class BimOpNode:
    #op
    #left
    #right
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right



if __name__ == '__main__':
    #text = '10+(19+1)*6/2-1'
    text = '1+2 > 3+4'
    l = Lexer(text)
    tokens = l.lex()
    for t in tokens:
        print("value: {}, token: {}".format(t.text, t.type))

    parser = Parser(tokens)
    #ast = parser.expr()
    ast = parser.logic_expr()
    print(ast)
    result = parser.eval(ast)

    print(result)
