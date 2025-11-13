CXX = g++

CXXFLAGS = -Wall -Wextra -Isrc/cpp -Isrc/cpp/geometricObjects $(shell python3-config --cflags)

LDFLAGS = $(shell python3-config --embed --ldflags 2>/dev/null || python3-config --ldflags)

BUILD_DIR = build
TARGET = main

# 1. Liste seus fontes
SRCS_MAIN = main.cpp menu.cpp plotter.cpp calculator.cpp
SRCS_GEO = geometricObjects/circumference.cpp geometricObjects/polygon.cpp geometricObjects/line.cpp geometricObjects/vector2d.cpp

SRCS_CPP = $(addprefix src/cpp/, $(SRCS_MAIN))
SRCS_GEO_CPP = $(addprefix src/cpp/, $(SRCS_GEO))
SRCS = $(SRCS_CPP) $(SRCS_GEO_CPP)

# 2. Gere a lista de OBJS MANTENDO a estrutura de pastas
#    Isto transforma "src/cpp/main.cpp" em "build/main.o"
#    E "src/cpp/geometricObjects/point.cpp" em "build/geometricObjects/point.o"
OBJS = $(patsubst src/cpp/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# 3. Regras principais
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# 4. A REGRA DE PADRÃO MÁGICA (Substitui todas as regras .o explícitas)
#    Esta regra única lida com TUDO:
$(BUILD_DIR)/%.o: src/cpp/%.cpp
	@mkdir -p $(dir $@)  # <--- AQUI ESTÁ A MÁGICA!
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 5. Limpeza
clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)


# Debug
debug: CXXFLAGS += -DDEBUG -g
debug: clean $(TARGET)
