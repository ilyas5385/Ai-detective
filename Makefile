CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -g
LDFLAGS = -lm

TARGET = detective_ai
SOURCES = detective_demo.c tunnel_system.c hunter_region.c reasoning_region.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = tunnel_system.h hunter_region.h reasoning_region.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "✅ Build complete: ./$(TARGET)"

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Cleaned build files"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
