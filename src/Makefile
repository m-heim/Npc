npcc: npcc.o parser.o scanner.o token.o token_tree.o symbol_table.o
	gcc -o ../build/npcc npcc.o parser.o scanner.o token.o token_tree.o symbol_table.o
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
token.o: token.c
	gcc -c token.c
	@echo "compiling token"
symbol_table.o: symbol_table.c
	gcc -c symbol_table.c
	@echo "compiling symbols"
token_tree.o: token_tree.c
	gcc -c token_tree.c
	@echo "compiling token_tree"
clean:
	rm *.o npcc
