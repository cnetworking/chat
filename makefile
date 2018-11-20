SRC = src/
BIN = bin/

CC = gcc

CLIENT_SRC = $(SRC)client.c
SERVER_SRC = $(SRC)server.c

client: $(CLIENT_SRC)
	$(CC) -o $(BIN)$@ $(CLIENT_SRC) $(FLAGS)
server: $(SERVER_SRC)
	$(CC) -o $(BIN)$@ $(SERVER_SRC) $(FLAGS)
all:
	make client
	make server
clean:
	rm -rf $(BIN)*
