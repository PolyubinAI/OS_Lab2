FLAGS = -std=c99
СС = gcc
all: main child1 child2

main: main.c
	$(CC) $(FLAGS) main.c -o main

child1: child1.c
	$(CC) $(FLAGS) child1.c -o child1

child2: child2.c
	$(CC) $(FLAGS) child2.c -o child2

clean:
	rm main child1 child2
