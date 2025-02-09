CC = gcc
CFLAGS = -Wall
SRC_DIR = src
PROT_DIR = prot
OBJ_DIR = obj
BIN = simulateur

SRCS = $(SRC_DIR)/asmHex.c $(SRC_DIR)/cpu.c $(SRC_DIR)/main.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(PROT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

re: clean $(BIN)

.PHONY: clean re
