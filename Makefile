CC = g++
CFLAGS = -std=c++17 -pedantic -c

all: main

benchmarks: benchmarks.o
	${CC} benchmarks.o -o benchmarks -lbenchmark

benchmarks.o: Benchmarks/benchmarks.cpp Container.hpp
	${CC} ${CFLAGS} Benchmarks/benchmarks.cpp

main: main.o 
	${CC} main.o -o main 

main.o: main.cpp Container.hpp
	${CC} ${CFLAGS} main.cpp

.PHONY: clean
clean:
	rm -f *.o main benchmarks core*

.PHONY: run
run:
	./main
