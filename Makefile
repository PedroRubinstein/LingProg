CXX = g++
CXXFLAGS = -Wall -Wextra $(shell python3-config --cflags)
# Use --embed to get -lpythonX.Y when embedding the interpreter (Python ≥3.8)
LDFLAGS = $(shell python3-config --embed --ldflags 2>/dev/null || python3-config --ldflags)

# Source and object files
SRCS = main.cpp menu.cpp circumference.cpp point.cpp polygon.cpp plotter.cpp
OBJS = main.o menu.o circumference.o point.o polygon.o plotter.o

# Output executable
TARGET = main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilation rule for .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug

debug: CXXFLAGS += -DDEBUG -g
debug: clean $(TARGET)
