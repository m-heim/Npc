import sys
import graphviz

class production_entry():

    def __init__(self, name):
        self.name = name
        self.productions: list[list[production_entry]] = []
        self.term = False
        self.first = set()
        self.follow = set()

    @staticmethod
    def remove_lr(self):
        pass

    def check_ll_one(self) -> bool:
        for production in self.productions:
            for production2 in [x for x in self.productions if not x == production]:
                factor = production_entry.longest_factor(production, production2)
                #print("longest factor for" + " " + self.name + " " + str(factor) + " " + str(set(production[factor].first).union(production2[factor].first)))
                print(self.name + " " + str(factor) + " " + str(len(production)) + " " + str(len(production2)))
                if factor == len(production):
                    if not production2[factor].first.isdisjoint(self.follow):
                        return False
                if factor == len(production2):
                    if not production[factor].first.isdisjoint(self.follow):
                        return False
                if factor == len(production) or factor == len(production2):
                    continue
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
            self.first = self.first.union(set([self]))
        else:
            for production in self.productions:
                self.first = self.first.union(production[0].set_first())
        return self.first
    def set_follow(self):
        for production in self.productions:
            for entry in range(len(production) - 1):
                if not production[entry].term:
                    production[entry].follow = production[entry].follow.union(production[entry + 1].first)
    def set_follow2(self):
        for production in self.productions:
            if not production[-1].term:
                production[-1].follow = production[-1].follow.union(self.follow)

class grammar():
    def __init__(self, file):
        self.productions = self.generate_productions(
            self.parse_productions(self.remove_comments_empty(self.read_file(file))))
        for production in filter(lambda x: x.term, self.productions):
            production.set_first()
        for production in filter(lambda x: not x.term, self.productions):
            production.set_first()
        for production in filter(lambda x: not x.term, self.productions):
            production.set_follow()
        for production in filter(lambda x: not x.term, self.productions):
            production.set_follow2()

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
        return "The grammar has no first-first conflicts: " + ret

    def remove_comments_empty(self, string: str):
        ret = []
        for line in string:
            if not line.startswith("//") and not line == "" and not line.startswith("#"):
                ret.append(line)
        return ret

    def __repr__(self):
        ret: str = ""
        ret += "####TERM####" + "\n"
        for production in filter(lambda x: x.term, self.productions):
            ret += production.name + ":" + " " + production.productions[0][0][1:-1] + " " + "\n"
        ret += "####PRODUCTIONS####" + "\n"
        for production in filter(lambda x: not x.term, self.productions):
            ret += production.name + ":" + " " + "\n"
            ret += "FIRST:" + " " + str(list(map(lambda x: x.name, production.first))) + "\n"
            ret += "FOLLOW:" + " " + str(list(map(lambda x: x.name, production.follow))) + "\n"
            for single_production in production.productions:
                ret += str([entry.name for entry in single_production]) + "\n"
        ret += str(self.verify())
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
