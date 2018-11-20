SRC = src
BIN = bin/

CC = gcc

SOURCE := $(shell find $(SRC) -name '*.c')
HEADERS = $(wildcard *.h)

client: $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SOURCE)
clean:
	rm -rf $(BIN)*