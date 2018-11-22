SRC = src/
BIN = bin/

CC = gcc
FLAGS = -std=c99

LIST = $(SRC)list/list.c
CLIENT_SRC = $(SRC)client.c $(SRC)strings.c $(LIST)
SERVER_SRC = $(SRC)server.c $(SRC)strings.c $(LIST)

HEADERS = $(SRC)chat.h $(SRC)list/list.h

client: $(CLIENT_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(CLIENT_SRC) $(FLAGS)
server: $(SERVER_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SERVER_SRC) $(FLAGS)
list_test: $(SRC)list/list_test.c $(LIST) $(HEADERS)
	$(CC) -o $(BIN)$@ $< $(LIST) $(FLAGS)
all:
	make client
	make server
	make list_test
clean:
	rm -rf $(BIN)*