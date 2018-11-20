SRC = src/
BIN = bin/

CC = gcc

CLIENT_SRC = $(SRC)client.c
SERVER_SRC = $(SRC)server.c

client: $(CLIENT_SRC)
	$(CC) -o $(BIN)$@ $(CLIENT_SRC)
server: $(SERVER_SRC)
	$(CC) -o $(BIN)$@ $(SERVER_SRC)
all:
	make client
	make server
clean:
	rm -rf $(BIN)*