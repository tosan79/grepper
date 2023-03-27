CC = g++
FLAGS = -std=c++17 -Wall -Wextra -pthread

grepper: main.o grepper.o threadpool.o
	$(CC) main.cpp grepper.cpp threadpool.cpp -o grepper $(FLAGS)

main.o: main.cpp grepper.h threadpool.h
	$(CC) -c main.cpp $(FLAGS)

grepper.o: grepper.cpp grepper.h threadpool.h
	$(CC) -c grepper.cpp $(FLAGS)

threadpool.o: threadpool.cpp threadpool.h
	$(CC) -c threadpool.cpp $(FLAGS)

make clean:
	rm *.o grepper