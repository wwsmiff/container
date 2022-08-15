CC = g++
CFLAGS = -std=c++17 -c

main: main.o
	${CC} main.o -o main 

main.o: main.cpp
	${CC} ${CFLAGS} main.cpp

.PHONY: clean
clean:
	rm -f *.o main

.PHONY: run
run:
	./main
