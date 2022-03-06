
CC=gcc
CFLAGS=-g -Wall -Werror
OBJS = obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o
DEPS = src/tensor_2d.h src/tensor_2d_threaded.h
BIN = bin/main

main: main.o tensor_2d.o tensor_2d_threaded.o
	$(CC) -o main main.o tensor_2d.o tensor_2d_threaded.o -pthread

main.o: main.c tensor_2d.c tensor_2d.h tensor_2d_threaded.c tensor_2d_threaded.h
	$(CC) -c main.c

tensor_2d.o: tensor_2d.c tensor_2d.h
	$(CC) -c tensor_2d.c

tensor_2d_threaded.o: tensor_2d.c tensor_2d.h tensor_2d_threaded.c tensor_2d_threaded.h 
	$(CC) -c tensor_2d_threaded.c -pthread

clean:
	rm *.o main