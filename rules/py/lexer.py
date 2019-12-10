from enum import Enum
import re

class TokenType(Enum):
    ADD = "\\+",
    SUB = "\\-",
    MUL = "\\*",
    DIV = "\\/",
    MORE = ">",
    LESS = "<",
    EMORE = ">=",
    ELESS = "<=",
    EQUIV = "=",
    ASSIGN = ":=",
    PRINT = "print",
    IF = 'if'
    THEN = 'then'
    ELSE = 'else'
    END = 'end'
    SEMICOLON = ';'
    SPACE = "[ \\t\\r\\n]+",
    LPAR = "\\(",
    RPAR = "\\)",
    ID = "[a-zA-Z_][a-zA-Z0-9_]*"
    NUMBER = "0|[1-9a-fA-F][0-9a-fA-F]*",


class Token:
    def __init__(self, type, text, pos):
        self.type = type
        self.text = text
        self.pos = pos


class Lexer:

    def __init__(self, src):
        self.src = src
        self.pos = 0
        self.tokens = []

    def nextToken(self):
        if self.pos >= len(self.src):
            return False

        for tt in TokenType:
            value = ""
            # prepare token value
            if not isinstance(tt.value, str):
                value = tt.value[0]
            else:
                value = tt.value

            result = re.match(value, self.src[self.pos::])

            if result is not None:
                # пробелы пропускаем
                if tt is not TokenType.SPACE:
                    t = Token(tt, result.group(0), self.pos)
                    self.tokens.append(t)
                self.pos = result.end() + self.pos
                return True

        raise Exception("Неожиданный символ {} в позиции {}".format(self.src[self.pos], self.pos));

    def lex(self):
        while self.nextToken():
            pass
        return self.tokens


if __name__ == '__main__':
    text = "10 + 20";
    l = Lexer(text);
    tokens = l.lex();
    for t in tokens:
        print("value: {}, token: {}".format(t.text, t.type))
