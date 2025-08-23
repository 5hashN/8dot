# compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c11 -Iinclude
LDFLAGS = -lm

# directories
SRC_DIR = src
OBJ_DIR = build
EXAMPLES_DIR = examples
EX_OBJ_DIR = build/examples

# core library sources (everything except main.c)
LIB_SRC = $(filter-out $(SRC_DIR)/main.c,$(wildcard $(SRC_DIR)/*.c))
LIB_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC))

# main.c for core executable
MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

# examples
EXAMPLES = $(wildcard $(EXAMPLES_DIR)/*.c)
EX_TARGETS = $(patsubst $(EXAMPLES_DIR)/%.c,$(EXAMPLES_DIR)/%,$(EXAMPLES))
EX_OBJ = $(patsubst $(EXAMPLES_DIR)/%.c,$(EX_OBJ_DIR)/%.o,$(EXAMPLES))

# default target
all: atedot $(EX_TARGETS)

# build core executable
atedot: $(LIB_OBJ) $(MAIN_OBJ)
	$(CC) $(LIB_OBJ) $(MAIN_OBJ) -o $@ $(LDFLAGS)

# build examples
$(EXAMPLES_DIR)/%: $(EX_OBJ_DIR)/%.o $(LIB_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# compile core library sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# compile main.c
$(OBJ_DIR)/main.o: $(MAIN_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ccmpile example sources
$(EX_OBJ_DIR)/%.o: $(EXAMPLES_DIR)/%.c | $(EX_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create build directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EX_OBJ_DIR):
	mkdir -p $(EX_OBJ_DIR)

# cebug build
debug: CFLAGS += -O0 -g
debug: clean all

# clean build files
clean:
	rm -rf $(OBJ_DIR) $(EX_OBJ_DIR) atedot $(EX_TARGETS)

.PHONY: all clean
