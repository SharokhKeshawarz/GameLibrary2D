CC = gcc
CXX = g++
EXE = bin/game
LIBRARY = bin/libgame.a

SRC_DIR = src
BIN_DIR = bin
OTHER_DIR = others
GLAD_DIR = $(OTHER_DIR)/glad
GLM_DIR = $(OTHER_DIR)/cglm/include
STB_IMAGE_DIR = $(OTHER_DIR)/stb_image
NUKLEAR_DIR = $(OTHER_DIR)/nuklear
INCLUDE_DIR = include

SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')
GLAD_FILE = $(GLAD_DIR)/glad.c
STB_IMAGE_FILE = $(STB_IMAGE_DIR)/stb_image.c

# Generate object file paths with the same directory structure as SRC_FILES
OBJS = 	$(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES)) \
		$(BIN_DIR)/glad.o $(BIN_DIR)/stb_image.o

OPENGL_LIBS = -ldl -lm -lX11 -lglfw -lm -lOpenGL -lGL -lpthread -lSDL2 -lSDL2_mixer -g
INCLUDE = -I$(INCLUDE_DIR) -I$(OTHER_DIR) -I$(GLAD_DIR) -I$(GLM_DIR) -I$(STB_IMAGE_DIR) -I$(NUKLEAR_DIR)

.PHONY: all clean re lib

all: $(EXE)

$(EXE): $(LIBRARY)

# Build the static library
$(LIBRARY): $(OBJS)
	ar rcs $(LIBRARY) $(OBJS)

# Rule to build object files in subdirectories
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/glad.o: $(GLAD_FILE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/stb_image.o: $(STB_IMAGE_FILE)
	@mkdir -p $(BIN_DIR)
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(EXE) $(LIBRARY) $(BIN_DIR)/*.o $(shell find $(BIN_DIR) -type f -name '*.o')

re: clean all
