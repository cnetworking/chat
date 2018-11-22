SRC = src/
BIN = bin/

CC = gcc
FLAGS = -std=c99

LIST = $(SRC)list/list.c
VECTOR = $(SRC)vector/vector.c
CLIENT_SRC = $(SRC)client.c $(SRC)strings.c $(LIST)
SERVER_SRC = $(SRC)server.c $(SRC)strings.c $(LIST)

HEADERS = $(SRC)chat.h $(SRC)list/list.h $(SRC)vector/vector.h

client: $(CLIENT_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(CLIENT_SRC) $(FLAGS)
server: $(SERVER_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SERVER_SRC) $(FLAGS)
vector: $(VECTOR) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SRC)vector/vector_test.c $(VECTOR) $(FLAGS)
list_test: $(SRC)list/list_test.c $(LIST) $(HEADERS)
	$(CC) -o $(BIN)$@ $< $(LIST) $(FLAGS)
sockets:
	make client
	make server
all:
	make client
	make server
	make list_test
clean:
	rm -rf $(BIN)*