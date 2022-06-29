CFLAGS=-DTEST

main : main.o display.o person.o elevator.o
	gcc -o main main.o display.o person.o elevator.o -lncurses

main.o : main.c
	gcc -c $(CFLAGS) main.c

display.o : display.c display.h
	gcc -c $(CFLAGS) display.c

person.o : person.c person.h
	gcc -c $(CFLAGS) person.c

elevator.o : elevator.c elevator.h
	gcc -c $(CFLAGS) elevator.c

run : main
	./main

clean :
	rm -f main *.o