# makefile
# Author: M00829986
# Created: 28/12/2024
# Updated: 1/12/2024

CC = g++

main: main.o classes.o
	$(CC) -o main main.o classes.o
	$(CC) test.cpp -o test classes.o

main.o: main.cpp classes.h
	$(CC) -c main.cpp

classes.o: classes.h


clean:
	-rm -f *.o
	-rm -f main
	-rm -f test
