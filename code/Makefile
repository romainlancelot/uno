executable : main.o game.o
	gcc -o executable main.o game.o

main.o : main.o
	gcc -c main.o

game.o : game.o game.h
	gcc -c game.c

clean :
	rm -Rf *.o *.gch executable