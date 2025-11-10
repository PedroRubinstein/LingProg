CXX = g++
CXXFLAGS = -Wall -Wextra

# Source and object files
SRCS = main.cpp menu.cpp circumference.cpp point.cpp polygon.cpp 
OBJS = main.o menu.o circumference.o point.o polygon.o

# Output executable
TARGET = main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

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
