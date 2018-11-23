SRC = src/
BIN = bin/

CC = gcc
FLAGS = -std=c99
# FLAGS = -std=c99 -g

LIST = $(SRC)list/list.c
VECTOR = $(SRC)vector/vector.c
CLIENT_SRC = $(SRC)client.c $(SRC)strings.c $(LIST)
SERVER_SRC = $(SRC)server.c $(SRC)strings.c $(LIST)

HEADERS = $(SRC)chat.h $(SRC)list/list.h $(SRC)vector/vector.h


sockets:
	make client
	make server
client: $(CLIENT_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(CLIENT_SRC) $(FLAGS)
server: $(SERVER_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SERVER_SRC) $(VECTOR) $(FLAGS)
vector_test: $(VECTOR) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SRC)vector/vector_test.c $(VECTOR) $(FLAGS)
list_test: $(SRC)list/list_test.c $(LIST) $(HEADERS)
	$(CC) -o $(BIN)$@ $< $(LIST) $(FLAGS)
test: src/test.c src/vector/vector.c  src/list/list.c
	$(CC) -o $(BIN)$@ $^ $(FLAGS)
all:
	make client
	make server
	make list_test
	make vector_test
clean:
	rm -rf $(BIN)*