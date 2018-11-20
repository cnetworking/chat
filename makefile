SRC = src
BIN = bin/

CC = g++
BOOST = -L /usr/local/lib/ -lboost_filesystem

SOURCE := $(shell find $(SRC) -name '*.cpp')
HEADERS = $(wildcard *.h)

main: $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SOURCE) $(BOOST)
clean:
	rm -rf $(BIN)*