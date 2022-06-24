main : main.o
	gcc -o main main.o -lncurses

main.o : main.c
	gcc -c main.c

run : main
	./main

clean :
	rm -f main *.o