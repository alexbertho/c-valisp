CC = gcc
CFLAGS = -Wall -ansi -pedantic -Iinclude
DEBUG_CFLAGS = -g3 -DDEBUG -O0
LIBS = -lreadline

# Définition des répertoires
BUILD_SOURCE_DIR = build/source
BUILD_TEST_DIR = build/test
BUILD_DEBUG_DIR = build/debug

# Structure des répertoires source et leurs équivalents dans build
SRC_DIRS = src/memory src/types src/primitives src/utils src/env src/io
TEST_DIRS = test/memory test/types test/primitives test/utils

# Fichiers source et leur transformation en objets
SRC_FILES = $(wildcard src/*/*.c src/*.c)
TEST_FILES = $(wildcard test/*.c test/*/*.c)

# Fichiers objets pour chaque type de build
OBJ_FILES = $(patsubst src/%.c,$(BUILD_SOURCE_DIR)/%.o,$(SRC_FILES))
DEBUG_OBJ_FILES = $(patsubst src/%.c,$(BUILD_DEBUG_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES = $(patsubst test/%.c,$(BUILD_TEST_DIR)/%.o,$(TEST_FILES))

# Binaires de sortie
MAIN_BIN = bin/valisp
DEBUG_BIN = bin/valisp_debug
TEST_BIN = bin/test_valisp

# Compilation des tests - besoin des fichiers source (sauf main.o) + fichiers de test
TEST_SRC_OBJ_FILES = $(filter-out $(BUILD_SOURCE_DIR)/main.o, $(OBJ_FILES))
APP_TEST_OBJ_FILES = $(TEST_SRC_OBJ_FILES) $(TEST_OBJ_FILES)

.PHONY: all clean dirs debug debug-dirs test test-dirs

# Cible par défaut - compilation standard
all: dirs $(MAIN_BIN)

# Création des répertoires
dirs:
	mkdir -p bin $(BUILD_SOURCE_DIR) $(patsubst src/%,$(BUILD_SOURCE_DIR)/%,$(SRC_DIRS))

debug-dirs:
	mkdir -p bin $(BUILD_DEBUG_DIR) $(patsubst src/%,$(BUILD_DEBUG_DIR)/%,$(SRC_DIRS))

test-dirs:
	mkdir -p bin $(BUILD_TEST_DIR) $(patsubst test/%,$(BUILD_TEST_DIR)/%,$(TEST_DIRS))

# Compilation de l'exécutable principal
$(MAIN_BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Compilation en mode debug
debug: debug-dirs $(DEBUG_BIN)

$(DEBUG_BIN): $(DEBUG_OBJ_FILES)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $^ -o $@ $(LIBS)

# Compilation et exécution des tests
# Note: les tests ont besoin des fichiers source compilés
test: dirs test-dirs $(TEST_BIN)
	./$(TEST_BIN)

# Compilation du binaire de test
$(TEST_BIN): $(APP_TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Règles de compilation
$(BUILD_SOURCE_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

$(BUILD_DEBUG_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -MMD -c $< -o $@

$(BUILD_TEST_DIR)/%.o: test/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -rf build bin

# Inclusion des fichiers de dépendances générés
-include $(wildcard $(BUILD_SOURCE_DIR)/**/*.d)
-include $(wildcard $(BUILD_DEBUG_DIR)/**/*.d)
-include $(wildcard $(BUILD_TEST_DIR)/**/*.d)