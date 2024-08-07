
CC=gcc
FLAGS=-Wall

output: main.o matrix.o nn.o
	$(CC) $(FLAGS) main.o matrix.o nn.o -o output

main.o: main.c
	$(CC) $(FLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(FLAGS) -c matrix.c

nn.o: nn.c nn.h
	$(CC) $(FLAGS) -c nn.c
clean:
	rm *.o output
