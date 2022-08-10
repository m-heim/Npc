import sys
import graphviz


class production_entry():

    def __init__(self, name):
        self.name = name
        self.productions = []
        self.term = False
        self.first = set()

    @staticmethod
    def remove_lr(self):
        pass

    def __repr__(self) -> str:
        ret = ""
        if self.term:
            ret = self.productions[0][0]
        else:
            for prod in self.productions:
                ret += "["
                for symb in prod:
                    ret += symb.name + "," + str(symb.term) + ":"
                ret += "]"
        return "[" + self.name + "," + str(self.term) + "->" + ret + "]" + "\n"

    def check_ll_one(self) -> bool:
        for production in self.productions:
            for production2 in [x for x in self.productions if not x == production]:
                factor = production.longest_factor(production, production2)
                if factor == len(production) or factor == len(production2):
                    continue
                #print("longest factor for" + " " + self.name + " " + str(factor) + " " + str(set(production[factor].first).union(production2[factor].first)))
                if not set(production[factor].first).isdisjoint(production2[factor].first):
                    return False
        return True

    @staticmethod
    def longest_factor(lst1, lst2):
        for i in range(min([len(lst1), len(lst2)])):
            if not lst1[i] == lst2[i]:
                return i
        return min([len(lst1), len(lst2)])

    def set_first(self):
        if self.term:
            return self
        else:
            for production in self.productions:
                self.first = self.first.union(production[0].set_first())
                return self.first 


class grammar():
    def __init__(self, file):
        self.productions = self.generate_productions(
            self.parse_productions(self.remove_comments_empty(self.read_file(file))))
        for production in filter(lambda x: not x.term, self.productions):
            production.set_first()

    def read_file(self, filename: str) -> list[str]:
        with open(filename) as file:
            return file.read().splitlines()

    def parse_productions(self, lst: list[str]) -> list[list]:
        ret = []
        for line in lst:
            splitted = line.split("::=")
            right = splitted[1].strip()
            left = splitted[0].strip()
            if right.startswith("\""):
                prods = [[right]]
            else:
                prods = [[y.replace(">", "").replace(
                    "<", "") for y in x.strip().split(" ")] for x in right.split("|")]
            ret.append([left, prods])
        return ret

    def generate_productions(self, productions: list) -> None:
        ret: list[production_entry] = []
        for name in map(lambda x: x[0], productions):
            ret.append(production_entry(name))
        for prod in productions:
            cur = grammar.find_production(prod[0], ret)
            if prod[1][0][0].startswith("\""):
                cur.term = True
                cur.productions = prod[1]
            else:
                cur.term = False
                for single_prod in prod[1]:
                    cur.productions.append(
                        [grammar.find_production(x, ret) for x in single_prod])
        return ret
    @staticmethod
    def find_production(name, productions) -> production_entry:
        for prod in productions:
            if prod.name == name:
                return prod
        print("couldnt find " + name)
        raise Exception
        return

    def verify(self) -> bool:
        lst = [prod.check_ll_one() for prod in self.productions]
        ret = str(all(lst))
        print("The grammar has no first-first conflicts: " + ret)

    def remove_comments_empty(self, string: str):
        ret = []
        for line in string:
            if not line.startswith("//") and not line == "" and not line.startswith("#"):
                ret.append(line)
        return ret

    def __repr__(self):
        ret: str = ""
        ret.append("####TERM####")
        for production in filter(lambda x: x.term, self.productions):
            ret.append(production.name + ":" + " " +
                       production.productions[0][0][1:-1] + " " + "\n")
        ret.append("####PRODUCTIONS####")
        for production in filter(lambda x: not x.term, self.productions):
            ret.append(production.name + ":" + " " + "\n")
            ret.append(str(production.first) + "\n")
            for single_production in production.productions:
                ret.append(
                    str([entry.name for entry in single_production]) + "\n")
        ret.append(self.verify())
        return ret


""" 
class bnf_syntax_tree():
    dot = graphviz.Digraph('graph', comment='the syntax graph')

    def __init__(self, productions: production):
        self.productions = productions
        self.out = []
        bnf_syntax_tree.dot.node(str(id(self)), self.productions.name)
        if not productions.term:
            for production in productions.productions:
                tree = self
                for symbol in production:
                    if symbol == productions:
                        tree.out.append(self)
                    else:
                        tree.out.append(bnf_syntax_tree(symbol))
                    bnf_syntax_tree.dot.edge(
                        str(id(tree)), str(id(tree.out[-1])))
                    bnf_syntax_tree.dot.render(directory='tree')
                    tree = tree.out[-1]

    def add(self, symbol):
        self.out.append(symbol) """


def main2():
    g = grammar(sys.argv[1])
    print(g)


if __name__ == '__main__':
    main2()
