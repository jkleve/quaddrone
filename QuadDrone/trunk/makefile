SRC_FILES = main.c
OBJ_FILES = $(SRC_FILES:.c=.o)
INC_DIRS = -I/usr/local/avr/lib/gcc/avr/5.2.0/include \
-I/usr/local/avr/include \
-I/usr/local/avr/avr/include
# don't include standard c library
DIS_INC = -nostdinc
OUTPUT = main

PROG = dragon_isp
PORT = usb
MCU = m2560
#MCU = atmega2560

CC = avr-gcc
CFLAGS = $(DIS_INC) $(INC_DIRS) -mcall-prologues -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=$(MCU) -Wall -Wstrict-prototypes -O2
OBJCOPY = avr-objcopy
RM = rm -f
ECHO =  echo

# make hex file
all: $(OUTPUT).elf
	@$(ECHO) Making hex
	@$(OBJCOPY) -R .eeprom -O ihex $(OUTPUT).elf $(OUTPUT).hex
	@$(ECHO) Build complete

# link
$(OUTPUT).elf: $(OBJ_FILES)
	@$(ECHO) Linking $@
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(OUTPUT).elf -Wl,-Map,$(OUTPUT).map

# object files
$(OBJ_FILES): %.o : %.c
	@$(ECHO) Compiling $<
	@$(CC) -c $(CFLAGS) $< -o $@

# load
load: 
	avrdude -p $(MCU) -c $(PROG) -P $(PORT) -e -U flash:w:$(OUTPUT).hex

clean:
	@$(ECHO) Removing all generated files
	@$(RM) $(OBJ_FILES) $(OUTPUT).elf $(OUTPUT).map $(OUTPUT).hex
