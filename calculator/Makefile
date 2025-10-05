CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
TARGET = calc5
SOURCES = calc5.cpp
OBJECTS = $(SOURCES:.cpp=.o)
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
# Тест
test: $(TARGET)
	@echo "v Тестирование калькулятора v"
	@echo "Справка тест"
	./$(TARGET)
	@echo
	@echo "Среднее арифметическое тест"
	./$(TARGET) -o average 5 10 15 20 25
	@echo
	@echo "Медиана тест"
	./$(TARGET) -o median 1 2 3 4 5 
	@echo
	@echo "Медиана с четным кол тест"
	./$(TARGET) -o median 1 2 3 4 5 6
.PHONY: all clean install test
