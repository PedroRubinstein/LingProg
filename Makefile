TARGET_EXEC := cartesia

BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include
BIN_DIR := ./bin

# Find all source files (including subdirectories)
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Create object file names mapped to the build directory
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Dependency files to track header changes automatically
DEPS := $(OBJS:.o=.d)

# Compiler settings
CXX := g++
# Note: We include both include/ and include/geometricObjects to keep your 
# existing short #include "vector2d.h" syntax working.
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP \
            -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/geometricObjects \
            $(shell python3-config --cflags)

# Linker settings (for Python embedding)
# We add -Wl,-rpath to tell the loader where to find libpython at runtime
PYTHON_LIB_PATH := $(shell python3-config --prefix)/lib
LDFLAGS := $(shell python3-config --embed --ldflags 2>/dev/null || python3-config --ldflags) \
           -Wl,-rpath,$(PYTHON_LIB_PATH)

# --- Rules ---

# 1. Link the final executable
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking $(TARGET_EXEC)..."
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $(BIN_DIR)/$(TARGET_EXEC)"

# 2. Compile C++ source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# 3. Include dependency info
-include $(DEPS)

.PHONY: all clean run debug

all: $(BIN_DIR)/$(TARGET_EXEC)

run: $(BIN_DIR)/$(TARGET_EXEC)
	@echo "Running Application..."
	@./$(BIN_DIR)/$(TARGET_EXEC)

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: clean all
