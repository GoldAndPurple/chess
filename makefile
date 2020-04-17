OUT = bin/chess
CC = gcc
CFLAGS = -Wall -Werror -c
ODIR = build
SDIR = src

OBJS = $(ODIR)/board_print_terminal.o $(ODIR)/board.o $(ODIR)/main.o

all: $(OUT)

$(ODIR)/board_print_terminal.o: $(SDIR)/board_print_terminal.c
		$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/board.o: $(SDIR)/board.c
		$(CC) $(CFLAGS) -o $@ $^

$(ODIR)/main.o: $(SDIR)/main.c
		$(CC) $(CFLAGS) -o $@ $^

$(OUT): $(OBJS) 
		$(CC) -g1 -o $(OUT) $^

.PHONY: all clean

clean:
		rm -f $(ODIR)/*.o $(OUT)