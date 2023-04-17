prog: main.o
	g++ -fopenmp -g main.o -o ourProg

main.o: main.cpp ChainingHash.h ProbingHash.h
	g++ -fopenmp -c -g -Wall -std=c++11 main.cpp

clean: 
	-rm *.o

run:
	@./ourProg