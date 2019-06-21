CC=g++
CFLAGS=-march=native -flto -O3 -std=c++17
INCLUDES = -Iinclude
TARGET = cpmaker
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}}

all:
	@mkdir -p $(OBJ_DIR)
	$(MAKE) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $@

clean:
	rm -rf obj/* cpmaker 

dist-clean: clean
	rm -rf *pdf *ly *midi
