
CC = gcc
CFLAGS = -g -Wall -Werror

SDIR = src
ODIR = obj
BDIR = bin

OBJS = $(ODIR)/main.o $(ODIR)/tensor_2d.o $(ODIR)/tensor_2d_threaded.o $(ODIR)/NN_activations.o $(ODIR)/NN_layers.o $(ODIR)/NN_models.o


$(SDIR)/main: $(OBJS)
	$(CC) -o $(BDIR)/main $(OBJS) -pthread

$(ODIR)/main.o: $(SDIR)/main.c
	$(CC) -o $(ODIR)/main.o -c $(SDIR)/main.c $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(SDIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm obj/* bin/*