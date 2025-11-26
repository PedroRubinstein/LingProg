TARGET_EXEC := cartesia

BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include
BIN_DIR := ./bin

# Find all .cpp files recursively (includes src/algorithms/*.cpp)
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Map source objects to build directory
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Python Configuration
PYTHON_CFLAGS := $(shell python3-config --cflags)
PYTHON_LDFLAGS := $(shell python3-config --embed --ldflags 2>/dev/null || python3-config --ldflags)
PYTHON_LIB_PATH := $(shell python3-config --prefix)/lib

# Compiler Settings
CXX := g++

# UPDATED: Added include for algorithms and -flto=auto
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP \
            -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/geometricObjects \
            -I$(INCLUDE_DIR)/algorithms \
            $(PYTHON_CFLAGS) -flto=auto

# Linker Settings
# UPDATED: Added -flto=auto
LDFLAGS := $(PYTHON_LDFLAGS) -Wl,-rpath,$(PYTHON_LIB_PATH) -flto=auto

# Libraries
LDLIBS := -lsqlite3

# --- Rules ---

.PHONY: all clean run debug

all: $(BIN_DIR)/$(TARGET_EXEC)

# Linking Rule
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking $(TARGET_EXEC)..."
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Build complete: $(BIN_DIR)/$(TARGET_EXEC)"

# Compilation Rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN_DIR)/$(TARGET_EXEC)
	@echo "Running Application..."
	@./$(BIN_DIR)/$(TARGET_EXEC)

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: clean all

-include $(DEPS)
