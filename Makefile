CC = g++
FLAGS = -std=c++17 -Wall -Wextra

grepper: main.o threadpool.o
	$(CC) main.cpp threadpool.cpp -o grepper $(FLAGS)

main.o: main.cpp grepper.h
	$(CC) -c main.cpp $(FLAGS)

threadpool.o: threadpool.cpp grepper.h
	$(CC) -c threadpool.cpp $(FLAGS)

make clean:
	rm *.o grepper