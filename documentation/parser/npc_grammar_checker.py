import sys
class production():
    all_productions = []
    def __init__(self, name):
        self.name = name
        self.productions = []
    @staticmethod
    def add_prototypes(productions):
        for prod in productions:
            production.all_productions.append(production(prod[0]))
    def find_production(self, name):
        for prod in production.all_productions:
            if prod.name == name:
                return prod
        raise Exception
        return
    def update_productions(self, productions: list):
        print(productions)
        for prod in productions:
            self.productions.append([[self.find_production(token.replace("?", "")), not token.endswith("?")] for token in prod])
    def update_tokens(self, token: list[str]):
        self.productions = [[[token, True]]]
    def check_first(self):
        for prod in self.productions:
            
    def __repr__(self) -> str:
        return self.name
class checker():
    def __init__(self, tokens: str, productions: str):
        self.tokens = self.parse_tokens(tokens)
        self.productions = self.parse_productions(productions)
    @staticmethod
    def parse_tokens(tokens: str):
        x = [x for x in tokens.splitlines() if (not x.startswith("//") and not x.__eq__(""))]
        for i in range(len(x)):
            x[i] = [x[i].split("::=")[0].strip(), x[i].split("::=")[1].strip()]
        return x
    @staticmethod
    def parse_productions(productions: str):
        x = [x for x in productions.splitlines() if (not x.startswith("//") and not x.__eq__(""))]
        for i in range(len(x)):
            left = x[i].split("::=")[0]
            right = x[i].split("::=")[1].strip()
            x[i] = [left.strip(), []]
            for y, prod in enumerate(right.split("|")):
                x[i][1].append([token.replace(">", "").replace("<","").replace("//", "").strip() for token in prod.strip().split(" ")])
        return x
        
def main():
    with open(sys.argv[1]) as f:
        content = f.read()
    tokens = content[content.index("#tokens") + len("#tokens"):content.index("#endtokens")]
    productions = content[content.index("#productions") + len("#productions"):content.index("#endproductions")]
    check = checker(tokens, productions)
    tokens = check.parse_tokens(tokens)
    productions = check.parse_productions(productions)
    print(tokens)
    print(productions)
    production.add_prototypes(tokens + productions)
    for i, prod in enumerate(production.all_productions[:len(tokens)]):
        prod.update_tokens(tokens[i][1])
    for i, prod in enumerate(production.all_productions[len(tokens):]):
        prod.update_productions(productions[i][1])
    for prod in productions:
        if prod[0] not in map(lambda y: y.name, production.all_productions):
            print(prod[0])
    for prod in production.all_productions:
        print(prod.name, prod.productions)
if __name__ == '__main__':
    main()