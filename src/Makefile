prog: slangc.o
	gcc -o slangc slangc.o parser.o scanner.o token.o token_tree.o
slangc.o: slangc.c
	gcc -c slangc.c
parser.o: parser.c
	gcc -c parser.c
scanner.o: scanner.c
	gcc -c scanner.c
token.o: token.c
	gcc -c token.c
token_tree.o: token_tree.c
	gcc -c token_tree.c
