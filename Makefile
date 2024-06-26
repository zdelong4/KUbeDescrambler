CC = g++
CFLAGS = -Wall -g

main: main.o cube.o solver.o
	$(CC) $(CFLAGS) -o main main.o cube.o solver.o

main.o: main.cpp cube.hpp solver.hpp
	$(CC) $(CFLAGS) -c main.cpp

cube.o: cube.hpp solver.hpp

solver.o: solver.hpp cube.hpp