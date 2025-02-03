# You may include test files for checking functions as well..
# I will try to include a few....

CXX = g++
CXXFlags = -std=c++17 -Icompiler/include -Wall

# Directories
SRC_DIR = compiler/src
OBJ_DIR = compiler/obj
BIN_DIR = compiler/bin

# Source and object files:
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/compiler

# Build the compiler executable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFlags) $^ -o $@
	@echo "Building compiler executable..."

# compile each .cpp file into an object file...
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFlags) -c $< -o $@

# clean build files
clean:
	- del /s /q $(OBJ_DIR)\* $(BIN_DIR)\*
	- rmdir /s /q $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean