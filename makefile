
CC=gcc
CFLAGS=-I -g -Wall -Werror

SDIR = src
ODIR = obj
BDIR = bin

OBJS = $(ODIR)/main.o $(ODIR)/tensor_2d.o $(ODIR)/tensor_2d_threaded.o

DEPS=src/tensor_2d.h src/tensor_2d_threaded.h

$(SDIR)/main: $(OBJS)
	$(CC) -o $(BDIR)/main $(ODIR)/main.o $(ODIR)/tensor_2d.o $(ODIR)/tensor_2d_threaded.o -pthread

$(ODIR)/main.o: $(SDIR)/main.c
	$(CC) -o $(ODIR)/main.o -c $(SDIR)/main.c $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(SDIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm obj/* bin/*