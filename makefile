CC=gcc
CFLAGS=-ansi -Wall -pedantic

all : main.o binary.o common.o name.o principals.o title.o
	$(CC) $(CFLAGS) -o a3 main.o binary.o common.o name.o principals.o title.o

main.o: main.c binary.h common.h name.h principals.h title.h
	$(CC) $(CFLAGS) -c main.c -o main.o

binary.o: binary.c binary.h common.h title.h
	$(CC) $(CFLAGS) -c binary.c -o binary.o

common.o: common.c binary.h common.h name.h principals.h title.h
	$(CC) $(CFLAGS) -c common.c -o common.o

name.o: name.c binary.h common.h name.h
	$(CC) $(CFLAGS) -c name.c -o name.o

principals.o: principals.c binary.h common.h principals.h
	$(CC) $(CFLAGS) -c principals.c -o principals.o

title.o: title.c binary.h common.h title.h
	$(CC) $(CFLAGS) -c title.c -o title.o

clean :
	rm bin/*
