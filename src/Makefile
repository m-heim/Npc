npcc: npcc.o parser.o scanner.o token.o token_tree.o
	gcc -o npcc npcc.o parser.o scanner.o token.o token_tree.o symbols.o
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
symbols.o: symbols.c
	gcc -c symbols.c
	@echo "compiling symbols"
token_tree.o: token_tree.c
	gcc -c token_tree.c
	@echo "compiling token_tree"
clean:
	rm *.o npcc
