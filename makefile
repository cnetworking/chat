SRC = src/
BIN = bin/

CC = gcc
# FLAGS = -g

SOURCE = $(SRC)strings.c $(SRC)getline.c $(SRC)list/list.c
# SOURCE = $(SRC)strings.c $(SRC)getline.c
HEADERS = $(SRC)chat.h $(SRC)list/list.h
HEADERS = $(SRC)chat.h

client: $(SRC)client.c $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SRC)client.c $(SOURCE) $(FLAGS)
server: $(SRC)server.c $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SRC)server.c $(SOURCE) $(FLAGS)
list_test: $(SRC)list/list_test.c $(SRC)list/list.c $(SRC)list/list.h
	$(CC) -o $(BIN)$@ $(SRC)list/list_test.c $(SRC)list/list.c $(FLAGS)
all:
	make client
	make server
	make list_test
clean:
	rm -rf $(BIN)*