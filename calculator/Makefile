CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = calc5
SOURCES = calc5.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Тест
test: $(TARGET)
	@echo "Тестирование калькулятора"
	@echo "Справка тест"
	./$(TARGET)
	@echo
	@echo "Среднее арифметическое тест"
	./$(TARGET) -o average 5 10 15 20 25
	@echo
	@echo "Тест 3: Медиана"
	./$(TARGET) -o median 1 2 3 4 5
	@echo
	@echo "Тест 4: Медиана с четным количеством чисел"
	./$(TARGET) -o median 1 2 3 4 5 6
.PHONY: all clean install test