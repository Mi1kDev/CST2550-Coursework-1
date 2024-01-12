# makefile
# Author: M00829986
# Created: 28/12/2023
# Updated: 12/1/2024

CC = g++

main: main.o person.o member.o book.o librarian.o
	$(CC) -o main main.o person.o member.o book.o librarian.o
	$(CC) test.cpp -o test person.o member.o book.o librarian.o

main.o: main.cpp person.h member.h book.h librarian.h
	$(CC) -c main.cpp

person.o: person.h

member.o: member.h

book.o: book.h

librarian.o: librarian.h

.PHONY: clean

clean:
	-rm -f *.o
	-rm -f main
	-rm -f test
