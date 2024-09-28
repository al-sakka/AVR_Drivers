# MCU and flags
MCU = atmega32
F_CPU = 16000000UL
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Directories and file names
SRC_DIR = .
TARGET = main

# Find all .c files in the current directory and subdirectories
SRC = $(shell find $(SRC_DIR) -name '*.c')

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET).hex

# Rule to compile .c files into .o files
%.o: %.c
	avr-gcc $(CFLAGS) -c $< -o $@

# Rule to create the .elf file
$(TARGET).elf: $(OBJ)
	avr-gcc -mmcu=$(MCU) -o $@ $(OBJ)

# Rule to create the .hex file from the .elf file
$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

# Flash the microcontroller
flash: $(TARGET).hex
	avrdude -c usbasp -p m32 -U flash:w:$(TARGET).hex:i

# Clean up the generated files
clean:
	rm -f *.o $(TARGET).elf $(TARGET).hex

.PHONY: all flash clean
