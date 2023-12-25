CC = g++

main: main.o classes.o
	$(CC) -o main main.o classes.o

main.o: main.cpp classes.h
	$(CC) -c main.cpp

classes.o: classes.h