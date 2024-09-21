# Compiler and Flags
CC = avr-gcc
CFLAGS = -mmcu=atmega32 -DF_CPU=16000000UL -Os -Wall -Iinclude

# Files
SRC = $(shell find . -name "*.c")
OBJ = $(SRC:.c=.o)
TARGET = main.hex

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
	avr-objcopy -O ihex -R .eeprom $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) *.hex

flash: $(TARGET)
	avrdude -c usbasp -p m32 -U flash:w:$(TARGET):i

program: $(TARGET)
	avrdude -c usbasp -p m32 -U flash:w:$(TARGET):i

.PHONY: all clean flash program
