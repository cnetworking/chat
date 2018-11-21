SRC = src/
BIN = bin/

CC = gcc

CLIENT_SRC = $(SRC)client.c $(SRC)concat.c
SERVER_SRC = $(SRC)server.c $(SRC)concat.c
HEADERS = $(SRC)chat.h

client: $(CLIENT_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(CLIENT_SRC) $(FLAGS)
server: $(SERVER_SRC) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SERVER_SRC) $(FLAGS)
all:
	make client
	make server
clean:
	rm -rf $(BIN)*