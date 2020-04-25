OUT = bin/chess
TEST = tester
CC = gcc
CFLAGS = -Wall -Werror -c
TESTFLAGS = -Wall -Isrc -Ithirdparty -c
ODIR = build
SDIR = src
TDIR = test

.PHONY: all clean

OBJS = $(ODIR)/board_print_terminal.o $(ODIR)/board.o $(ODIR)/main.o

all: $(OUT) $(TEST)
re: clean all

$(ODIR)/%.o: $(SDIR)/%.c
		$(CC) $(CFLAGS) -o $@ $^

$(OUT): $(OBJS)
		$(CC) -o $(OUT) $^

clean:
		rm -f $(ODIR)/*.o $(OUT) $(TEST)

#testing

$(ODIR)/%.o: $(TDIR)/%.c
		$(CC) $(TESTFLAGS) -o $@ $^

$(TEST): $(ODIR)/test_main.o $(ODIR)/test_board.o $(SDIR)/board.h
		$(CC) -o $(TEST) $^