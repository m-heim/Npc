npcc: npcc.o parser.o scanner.o token.o token_tree.o
	gcc -o npcc npcc.o parser.o scanner.o token.o token_tree.o symbol_table.o
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
token_tree.o: token_tree.c
	gcc -c token_tree.c
	@echo "compiling token tree"
symbol_table.o: symbol_table.c
	gcc -c symbol_table.c
clean:
	@echo "Cleaning.."
	rm *.o

