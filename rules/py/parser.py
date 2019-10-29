"""
Parser which works with tokens
"""
from lexer import Lexer, TokenType

class State:
    S_0 = 0
    S_FINAL = 1
    S_LOOP = 2


class Parser:

    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

    def match(self, expectedType):
        if self.pos < len(self.tokens):
            token = self.tokens[self.pos]
            if token.type == expectedType:
                self.pos += 1
                return True

        return False

    def newState(self, s):
        if s == State.S_0 or s == State.S_LOOP:
            if self.match(TokenType.NUMBER):
                return State.S_FINAL
            self.error("Ожидалось {}".format(TokenType.NUMBER))

        elif s == State.S_FINAL:
            if self.match(TokenType.ADD):
                return State.S_LOOP
            self.error("Ожидался {}".format(TokenType.ADD))

    def parse(self):
        e1 = self.slag()
        while (self.pos < len(self.tokens)):
            op = self.require(TokenType.ADD)
            e2 = self.slag()

            e1 = BimOpNode(op.text, e1, e2)

        return e1;


    def slag(self):
        e1 = self.require(TokenType.NUMBER)
        e1 = NumberNode(e1.text)
        while self.match(TokenType.MUL):
            op = self.tokens[self.pos-1]
            e2 = self.require(TokenType.NUMBER)
            e2 = NumberNode(e2.text)

            e1 = BimOpNode(op.text, e1, e2)

        return e1

    def elem(self):
        if self.match(TokenType.NUMBER):
            return NumberNode(self.tokens[self.pos])
        if self.match(TokenType.ID):
            return VarNode(self.tokens[self.pos])

        self.error("Ожидалось число или ид")


    def eval(self, n):
        if type(n) is NumberNode:
            return int(n.number)
        if type(n) is BimOpNode:
            l = self.eval(n.left)
            r = self.eval(n.right)
            return l+r if n.op == '+' else l*r

    def require(self, expected):
        if not self.match(expected):
            self.error("Ожидается " + expected.value[0] + " " + self.tokens[self.pos].text)
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
    text = '10 + 20 + 3 *      6'
    l = Lexer(text)
    tokens = l.lex()
    for t in tokens:
        print("value: {}, token: {}".format(t.text, t.type))

    parser = Parser(tokens)
    ast = parser.parse()

    result = parser.eval(ast)

    print(result)
