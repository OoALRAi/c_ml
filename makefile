
CC=gcc
FLAGS=-Wall

output: main.o matrix.o
	$(CC) $(FLAGS) main.o matrix.o -o output

main.o: main.c
	$(CC) $(FLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(FLAGS) -c matrix.c

clean:
	rm *.o output