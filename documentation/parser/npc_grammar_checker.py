import sys
class production():
    all_productions = []
    def __init__(self, name):
        self.name = name
        self.productions = []
        self.term: bool
    @staticmethod
    def add_prototypes(productions: dict):
        for nam in list(map(lambda x: x[0], productions)):
            production.all_productions.append(production(nam))
    @staticmethod
    def find_production(name):
        for prod in production.all_productions:
            if prod.name == name:
                return prod
        raise Exception
        return
    @staticmethod
    def update_productions(productions: list):
        for prod in productions:
            cur = production.find_production(prod[0])
            if prod[1][0][0][0].startswith("\""):
                cur.term = True
                productions = prod[1]
            else:
                production.find_production(prod[0]).term = False
                for prod2 in prod[1]:
                    cur.productions.append([[production.find_production(x[0]), x[1]] for x in prod2])
    def check_first(self):
        for prod in self.productions:
            pass
    def __repr__(self):
        return "[" + self.name + "," + str(self.productions) + "]"
def main2():
    productions: list
    with open(sys.argv[1]) as f:
        content = f.read()
    productions = gen_productions(remove_comments_empty(content.splitlines()))
    production.add_prototypes(productions)
    production.update_productions(productions)
    print(production.all_productions)

def remove_comments_empty(string: str):
    ret = []
    for line in string:
        if not line.startswith("//") and not line == "" and not line.startswith("#"):
            ret.append(line)
    return ret
def gen_productions(lst: list):
    ret = []
    for line in lst:
        splitted = line.split("::=")
        right = splitted[1].strip()
        left = splitted[0].strip()
        if right.startswith("\""):
            prods = [[[right, True]]]
        else:
            prods = [list(map(lambda y: [y.replace(">", "").replace("<", "").replace("?", ""), not "?" in y], x.strip().split())) for x in right.split("|")]
        ret.append([left, prods])
    return ret
if __name__ == '__main__':
    main2()
