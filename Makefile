CC = g++
CFLAGS = -std=c++17 -pedantic -c

main: main.o
	${CC} main.o -o main 

main.o: main.cpp Container.hpp
	${CC} ${CFLAGS} main.cpp

.PHONY: clean
clean:
	rm -f *.o main

.PHONY: run
run:
	./main
