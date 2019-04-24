CC = gcc
CFLAGS = -Wall

all: program
program: main.o functions.o
	gcc -o program main.o functions.o
main.o: main.c class.h
	gcc -c -Wall main.c

functions.o: functions.c class.h
	gcc -c  -Wall functions.c

clean:
	rm -f program main.o functions.o
