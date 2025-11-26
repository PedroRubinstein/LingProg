TARGET_EXEC := cartesia

BUILD_DIR := ./build
SRC_DIR := ./src
INCLUDE_DIR := ./include
BIN_DIR := ./bin

# Encontrar todos os arquivos .cpp recursivamente
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Mapear objetos para a pasta build
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Detectar configurações do Python
PYTHON_CFLAGS := $(shell python3-config --cflags)
PYTHON_LDFLAGS := $(shell python3-config --embed --ldflags 2>/dev/null || python3-config --ldflags)
PYTHON_LIB_PATH := $(shell python3-config --prefix)/lib

# Compilador
CXX := g++

CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP \
            -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/geometricObjects \
            $(PYTHON_CFLAGS)

# Flags do Linker (Onde procurar bibliotecas)
LDFLAGS := $(PYTHON_LDFLAGS) -Wl,-rpath,$(PYTHON_LIB_PATH)

# Bibliotecas Específicas (SQLite deve vir aqui!)
LDLIBS := -lsqlite3

# --- Regras ---

.PHONY: all clean run debug

all: $(BIN_DIR)/$(TARGET_EXEC)

# Regra de Linkagem: Observe que $(LDLIBS) está no FINAL
$(BIN_DIR)/$(TARGET_EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@echo "Linking $(TARGET_EXEC)..."
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "Build complete: $(BIN_DIR)/$(TARGET_EXEC)"

# Regra de Compilação
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
