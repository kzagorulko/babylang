
class State:
    S_0 = 0
    S_FINAL = 1
    S_LOOP = 2


class Parser:

    def __init__(self, text):
        self.symbols = text
        self.pos = 0

    def match(self, expected):
        if self.pos < len(self.symbols):
            ch = self.symbols[self.pos]
            if ch == expected:
                self.pos += 1
                return True

        return False

    def newState(self, s):
        if s == State.S_0 or s == State.S_LOOP:
            if self.match('4'):
                return State.S_FINAL
            self.error("Ожидалось 4")

        elif s == State.S_FINAL:
            if self.match('+'):
                return State.S_LOOP
            self.error("Ожидался +")

    def parse(self):
        s = State.S_0
        for i in range(0, len(self.symbols)):
            self.pos = i
            s = self.newState(s)

        return s == State.S_FINAL

    def error(self, msg):
        raise Exception("{} at {}".format(msg, self.pos))


if __name__ == '__main__':
    text = '4+4'
    parser = Parser(text)
    result = parser.parse()

    print(result)
