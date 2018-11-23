SRC = src/
BIN = bin/
BUILD = build/
MKDIR_P ?= mkdir -p

CC = gcc
FLAGS = -std=c99

server = server.c
client = client.c
SOURCE = $(shell find . -name "*.c" -not -name "$(server)" -not -name "$(client)")
HEADERS = $(shell find . -name "*.h")

all:
	make sockets
	make build
sockets:
	make client
	make server
client: $(SOURCE) $(HEADERS)
	make checkdir
	$(CC) -o $(BIN)$@ $(SRC)$($@) $(SOURCE) $(FLAGS)
server: $(SOURCE) $(HEADERS)
	make checkdir
	$(CC) -o $(BIN)$@ $(SRC)$($@) $(SOURCE) $(FLAGS)
checkdir:
	$(MKDIR_P) $(dir $(BIN))
.PHONY: build
build:
	make -f build.mk EXEC=server
	make -f build.mk EXEC=client
clean:
	rm -rf $(BIN)*
	rm -rf $(BUILD)*