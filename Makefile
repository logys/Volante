TARGET=volante
mmcu=atmega328p
programer=arduino
mcu=328p
port=/dev/ttyACM0

SRCDIR=./src
OBJECTDIR=./objects
BINDIR=./bin
VUSBDIR=./src/usbdrv

SOURCES :=$(wildcard $(SRCDIR)/*.c $(VUSBDIR)/*.c)
INCLUDES:=$(wildcard $(SRCDIR)/*.h $(VUSBDIR)/*.h)
OBJECTS	:=$(SOURCES:$(SRCDIR)/%.c=$(OBJECTDIR)/%.o)
ASMSOURCES :=$(wildcard $(VUSBDIR)/*.S)
rm=rm

CC=avr-gcc
CFLAGS=-Wall -O2 -mmcu=${mmcu} --std=gnu11 -DF_CPU=12000000UL -I./src/usbdrv

LINKER=avr-gcc
LFLAGS=-lm -Wall -mmcu=$(mmcu) -DF_CPU=12000000UL 

all:$(TARGET).hex

$(TARGET).hex:$(BINDIR)/$(TARGET)
	@avr-objcopy -O ihex $(BINDIR)/$(TARGET) $(BINDIR)/$(TARGET).hex
	@avr-size --mcu=${mmcu} -C --format=avr $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS) 
	@$(LINKER) $(OBJECTS) $(ASMSOURCES) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS):$(OBJECTDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

flash: $(TARGET).hex
	avrdude -p m328p -P /dev/ttyACM0 -c arduino -b 19200 -U flash:w:$(BINDIR)/$(TARGET).hex
