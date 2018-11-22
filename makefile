SRC = src/
BIN = bin/

CC = gcc
FLAGS = -g

SOURCE = $(SRC)strings.c $(SRC)getline.c $(SRC)list/list.c
HEADERS = $(SRC)chat.h $(SRC)list/list.h

client: $(SRC)client.c $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SRC)client.c $(SOURCE) $(FLAGS)
server: $(SRC)server.c $(SOURCE) $(HEADERS)
	$(CC) -o $(BIN)$@ $(SRC)server.c $(SERVER_SRC) $(FLAGS)
all:
	make client
	make server
clean:
	rm -rf $(BIN)*