CC=gcc
CFLAGS=-Wall -pedantic -std=c11
OBJ=blist.o
BIN=blisttest

all: $(BIN)


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(BIN).c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJ) $(BIN) *.dSYM
