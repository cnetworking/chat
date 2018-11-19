SRC = src
BIN = bin/

CC = g++
BOOST = -lboost_filesystem-mt

SOURCE := $(shell find $(SRC) -name '*.cpp')
HEADERS = $(wildcard *.h)

main: $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SOURCE) $(BOOST)
clean:
	rm -rf $(BIN)*