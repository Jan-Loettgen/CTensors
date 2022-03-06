
CC=gcc
CFLAGS=-I -g -Wall -Werror
OBJS = obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o
DEPS = src/tensor_2d.h src/tensor_2d_threaded.h
BIN = bin/main

bin/main: obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o
	$(CC) -o bin/ obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o

obj/main.o: src/main.c src/tensor_2d.c src/tensor_2d.h src/tensor_2d_threaded.c src/tensor_2d_threaded.h
	$(CC) -c obj/ src/main.c

obj/tensor_2d.o: src/tensor_2d.c src/tensor_2d.h
	$(CC) -c obj/ src/tensor_2d.c

obj/tensor_2d_threaded.o: src/tensor_2d.c src/tensor_2d.h src/tensor_2d_threaded.c src/tensor_2d_threaded.h 
	$(CC) -pthread -c obj/ src/tensor_2d_threaded.c