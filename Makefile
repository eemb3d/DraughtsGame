## Compiler
CC = gcc

SRC = ./src
TEST = ./test

# Flag 
CFLAGS = -Wall -pedantic -g

all: clean dama

test.o: $(TEST)/test.c 
	$(CC) $(CFLAGS) -c -o $@  $<

list.o: $(SRC)/list.c 
	$(CC) $(CFLAGS) -c -o $@  $<
	
search.o: $(SRC)/search.c 
	$(CC) $(CFLAGS) -c -o $@  $<

program-mv.o: $(SRC)/program-mv.c 
	$(CC) $(CFLAGS) -c -o $@  $<
	
player-mv.o: $(SRC)/player-mv.c 
	$(CC) $(CFLAGS) -c -o $@  $<
	
move.o: $(SRC)/move.c 
	$(CC) $(CFLAGS) -c -o $@  $<
	
init.o: $(SRC)/init.c 
	$(CC) $(CFLAGS) -c -o $@  $<

main.o: $(SRC)/main.c 
	$(CC) $(CFLAGS) -c -o $@  $<

DRAUGHTS = main.o init.o list.o search.o move.o program-mv.o player-mv.o test.o

dama : $(DRAUGHTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean dama

# Clean
clean:
	rm -f *~
	rm -f ./*.o
