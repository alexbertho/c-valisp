CC = gcc
CFLAGS = -Wall -ansi -pedantic -Iinclude
SRC_DIRS = src/memory src/types src/primitives src/utils src/tests
BUILD_DIRS = $(patsubst src/%,build/%,$(SRC_DIRS))
SRC_FILES = $(wildcard src/*/*.c src/*.c)
OBJ_FILES = $(patsubst src/%.c,build/%.o,$(SRC_FILES))

.PHONY: all clean dirs

all: dirs bin/valisp

dirs:
	mkdir -p bin $(BUILD_DIRS)

bin/valisp: $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -rf build bin

-include $(OBJ_FILES:.o=.d)
