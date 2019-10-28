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
        s = State.S_0
        for i in range(0, len(self.tokens)):
            self.pos = i
            s = self.newState(s)

        return s == State.S_FINAL

    def error(self, msg):
        raise Exception("{} at {}".format(msg, self.pos))


if __name__ == '__main__':
    text = '10+20'
    l = Lexer(text)
    tokens = l.lex()
    parser = Parser(tokens)
    result = parser.parse()

    print(result)
