npcc: npcc.o parser.o scanner.o token.o token_tree.o
	gcc -o npcc npcc.o parser.o scanner.o token.o token_tree.o symbol_table.o
npcc.o: npcc.c
	gcc -c npcc.c
parser.o: parser.c
	gcc -c parser.c
scanner.o: scanner.c
	gcc -c scanner.c
token.o: token.c
	gcc -c token.c
token_tree.o: token_tree.c
	gcc -c token_tree.c
symbol_table.o: symbol_table.c
	gcc -c symbol_table.c
clean:
	@echo "Cleaning.."
	rm *.o

