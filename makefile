
CC=gcc
FLAGS=-Wall

output: main.o matrix.o nn.o
	$(CC) $(FLAGS) main.o matrix.o nn.o -o output -lm


nn_square: nn_example_1.o matrix.o nn.o 
	$(CC) $(FLAGS) nn_example_1.o matrix.o nn.o -o nn_square -lm

nn_example_1.o: nn_example_1.c
	$(CC) $(FLAGS) -c nn_example_1.c

test_matrix: test_matrix.o matrix.o nn.o
	$(CC) $(FLAGS) test_matrix.o matrix.o nn.o -o test_matrix -lm

test_matrix.o: test_matrix.c
	$(CC) $(FLAGS) -c test_matrix.c

main.o: main.c
	$(CC) $(FLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(FLAGS) -c matrix.c

nn.o: nn.c nn.h
	$(CC) $(FLAGS) -c nn.c
clean:
	rm *.o output test_matrix nn_square
