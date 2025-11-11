CXX = g++
CXXFLAGS = -Wall -Wextra -I./geometricObjects $(shell python3-config --cflags)
# Use --embed to get -lpythonX.Y when embedding the interpreter (Python ≥3.8)
LDFLAGS = $(shell python3-config --embed --ldflags 2>/dev/null || python3-config --ldflags)

# Source and object files
SRCS = main.cpp menu.cpp geometricObjects/circumference.cpp geometricObjects/point.cpp geometricObjects/polygon.cpp geometricObjects/line.cpp plotter.cpp
OBJS = main.o menu.o circumference.o point.o polygon.o line.o plotter.o

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

# Explicit rules for geometric objects
circumference.o: geometricObjects/circumference.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

point.o: geometricObjects/point.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

polygon.o: geometricObjects/polygon.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

line.o: geometricObjects/line.cpp
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
