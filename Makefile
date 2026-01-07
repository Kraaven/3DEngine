# -----------------------------
# Compiler
# -----------------------------
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2

TARGET = MyRaylibApp
SRC_DIR = src
BUILD_DIR = builds

SRC = $(SRC_DIR)/main.c
OUT = $(BUILD_DIR)/$(TARGET).exe

RAYLIB_FLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

# -----------------------------
all: dirs $(OUT)

# -----------------------------
dirs:
	mkdir -p $(SRC_DIR) resources $(BUILD_DIR) etc

# -----------------------------
$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(RAYLIB_FLAGS)

# -----------------------------
clean:
	rm -rf $(BUILD_DIR)

# -----------------------------
run: all
	./$(OUT)
