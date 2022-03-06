
CC=gcc
CFLAGS=-g -Wall -Werror
OBJS = obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o
DEPS = src/tensor_2d.h src/tensor_2d_threaded.h
BIN = bin/main

bin/main: obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o
	$(CC) -o bin/main obj/main.o obj/tensor_2d.o obj/tensor_2d_threaded.o -pthread

obj/main.o: src/main.c src/tensor_2d.c src/tensor_2d.h src/tensor_2d_threaded.c src/tensor_2d_threaded.h
	$(CC) -o obj/main.o -c src/main.c $(CFLAGS)

obj/tensor_2d.o: src/tensor_2d.c src/tensor_2d.h
	$(CC) -o obj/tensor_2d.o -c src/tensor_2d.c $(CFLAGS)

obj/tensor_2d_threaded.o: src/tensor_2d.c src/tensor_2d.h src/tensor_2d_threaded.c src/tensor_2d_threaded.h 
	$(CC) -o obj/tensor_2d_threaded.o -c src/tensor_2d_threaded.c $(CFLAGS)

clean:
	rm obj/* bin/*