CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -pedantic
TARGET := ordenacao
SOURCE := src/main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).exe
