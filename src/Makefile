npcc: npcc.o parser.o scanner.o node.o ast.o symbol_table.o char_utils.o
	gcc -o ../build/npcc npcc.o parser.o scanner.o node.o ast.o symbol_table.o char_utils.o
	rm *.o
	@echo "linking"
npcc.o: npcc.c
	gcc -c npcc.c
	@echo "compiling main"
parser.o: parser.c
	gcc -c parser.c
	@echo "compiling parser"
scanner.o: scanner.c
	gcc -c scanner.c
	@echo "compiling scanner"
node.o: node.c
	gcc -c node.c
	@echo "compiling node"
symbol_table.o: symbol_table.c
	gcc -c symbol_table.c
	@echo "compiling symbols"
ast.o: ast.c
	gcc -c ast.c
	@echo "compiling ast.h"
char_utils.o: char_utils.c
	gcc -c char_utils.c
	@echo "compiling char_utils"
clean:
	rm *.o npcc
