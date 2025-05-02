CC = gcc
CFLAGS = -Wall -ansi -g -pedantic -Iinclude
SRC_DIRS = src/memory src/types src/primitives src/utils src/env src/io
TEST_DIRS = test/memory test/types test/primitives test/utils
BUILD_DIRS = $(patsubst src/%,build/%,$(SRC_DIRS)) build/test
SRC_FILES = $(wildcard src/*/*.c src/*.c)
TEST_FILES = $(wildcard test/*.c test/*/*.c)
OBJ_FILES = $(patsubst src/%.c,build/%.o,$(SRC_FILES))
TEST_OBJ_FILES = $(patsubst test/%.c,build/test/%.o,$(TEST_FILES))
LIBS = -lreadline

# Objets pour l'application principale (sans les objets de test)
MAIN_OBJ_FILES = $(OBJ_FILES) 

# Objets pour les tests (objets sources sans main + objets de test)
APP_TEST_OBJ_FILES = $(filter-out build/main.o, $(OBJ_FILES)) $(TEST_OBJ_FILES)
# Binaire de test
TEST_BIN = bin/test_valisp

.PHONY: all clean dirs test objext

all: dirs objext bin/valisp

dirs:
	mkdir -p bin $(BUILD_DIRS)

bin/valisp: $(MAIN_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Cible de test qui compile et exécute les tests
test: dirs objext $(TEST_BIN)
	./$(TEST_BIN)

# Compilation du binaire de test
$(TEST_BIN): $(APP_TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Règle pour compiler les fichiers source du projet
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Règle pour compiler les fichiers de test
build/test/%.o: test/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -rf build bin

-include $(wildcard build/**/*.d)		