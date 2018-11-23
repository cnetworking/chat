SRC = src/
BIN = bin/
BUILD = build/

CC = gcc
FLAGS = -std=c99
# FLAGS = -std=c99 -g

server = $(SRC)server.c
client = $(SRC)client.c

SOURCE = $(shell find . -name "*.c" -not -name "$(server)" -not -name "$(client)")
HEADERS = $(shell find . -name "*.h")

sockets:
	make client
	make server
client: $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $($@) $(SOURCE) $(FLAGS)
server: $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $($@) $(SOURCE) $(FLAGS)

.PHONY: build
build:
	make -f build.mk

clean:
	rm -rf $(BIN)*
	rm -rf $(BUILD)*