CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=gnu99 -O3
CLIBS=
SRC=src/interpreter
BUILD_DIR=build
OUT=bfi

all: $(OUT)

clean:
	rm -f $(OUT) **/*.o

$(BUILD_DIR)/interpreter.o: $(SRC).c $(SRC).h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC).c -o $@

bfi: main.c $(BUILD_DIR)/interpreter.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)
