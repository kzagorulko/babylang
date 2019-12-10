"""
Parser which works with tokens
"""
from lexer import Lexer, TokenType


class Parser:

    variables = {}

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

    def statement(self):
        list = []

        while self.match([TokenType.PRINT, TokenType.ID, TokenType.IF]):
            statement = self.tokens[self.pos-1]

            print(statement.type)
            print(statement.text)

            if statement.type == TokenType.PRINT:
                expr = self.expr()

                list.append(StatementNode(statement, expr))
            elif statement.type == TokenType.ID:
                print(self.tokens[self.pos].type)
                self.require([TokenType.ASSIGN])
                expr = self.expr()

                list.append(StatementNode(statement, expr))
            elif statement.type == TokenType.IF:
                expr = self.logic_expr()
                self.require([TokenType.THEN])

                node = StatementNode(statement, expr)
                list.append(node)
                node.s_then = self.statement()

                if self.match([TokenType.ELSE]):
                    node.s_else = self.statement()

                self.require([TokenType.END])

            self.require([TokenType.SEMICOLON])

        return list


    def eval_statement(self, list):
        for item in list:
            if type(item) is StatementNode:
                # print
                if item.statement.type == TokenType.PRINT:
                    print(self.eval(item.expr))

                # assign
                if item.statement.type == TokenType.ID:
                    self.variables[item.statement.text] = self.eval(item.expr)

                # if
                if item.statement.type == TokenType.IF:
                    if self.eval(item.expr):
                        self.eval_statement(item.s_then)
                    else:
                        self.eval_statement(item.s_else)

    def mnog(self):
        if self.match([TokenType.LPAR]):
            e = self.expr()
            self.require([TokenType.RPAR])
            return e
        else:
            e = self.require([TokenType.NUMBER, TokenType.ID])
            if e.type == TokenType.ID:
                e = VarNode(e.text)
            else:
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
            return int(str(n.number), 16)
        if type(n) is VarNode:
            return int(str(self.variables[n.var]), 16)
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
            elif n.op == '=':
                return l==r

    def require(self, expecteds):
        if not self.match(expecteds):
            self.error("Ожидалось " + expecteds[0].value[0] + " " + self.tokens[self.pos].text)
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

class StatementNode:
    #statement;
    def __init__(self, statement, ast):
        self.statement = statement
        self.expr = ast
        self.s_then = []
        self.s_else = []

    def append(self, statement):
        self.list.append(statement)


if __name__ == '__main__':
    # text = '10+(19+1)*6/2-1'
    # text = '1+2 > 3+4'
    # statement print
    text = """
        print 1a;
        if 1+1 > 0 then
            print 10*10/5;
            a := 3;
            print a+2;
            a := a * 2;

            if a > 5 then
                print 100;
            else
                print 200;
            end;
        end;
        b := 23f;
    """
    
    l = Lexer(text)
    tokens = l.lex()
    for t in tokens:
        print("value: {}, token: {}".format(t.text, t.type))

    parser = Parser(tokens)
    #ast = parser.expr()
    #ast = parser.logic_expr()
    ast = parser.statement()
    print(ast)
    print("--- EXEC ---")
    result = parser.eval_statement(ast)
    print(parser.variables)
