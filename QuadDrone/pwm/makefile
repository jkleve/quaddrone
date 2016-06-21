# Available targets:
# make all /Do everything (main.elf and main.hex)
# make load /Program the device
# make dload /Program the device and start debugging
# make debug /Start debugging
# make clean /Clean
# make size /Get information about memory usage
# make filename.s /Generate assembler file from a C source
# make filename.o /Generate object file from a C source
#Source files
SRC_FILES=\
main.c led.c comm.c
#Object files
PROCESS_FILES=$(SRC_FILES:.c=.e)
OBJ_FILES=$(SRC_FILES:.c=.o)
#Directories where to look for include files
INC_DIRS=\
-I. \
#Output file name
OUTPUT=pwm
#Programmer and port
PROG=dragon_isp

PORT=usb
#Debugging host and port
DHOST=localhost
DPORT=6423
#Compiler related params
MCU=atmega2560
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS= -mcall-prologues -std=gnu99 -funsigned-char -funsigned-bitfields \
-fpack-struct -fshort-enums -mmcu=$(MCU) -Wall -Wstrict-prototypes \
$(INC_DIRS)
#Optimization level
CFLAGS+=-Os
#Debug info
CFLAGS+=-gdwarf-2

#Generate hex file ready to upload
all: $(OUTPUT).elf
	$(OBJCOPY) -R .eeprom -O ihex $(OUTPUT).elf $(OUTPUT).hex
#	@echo "--------------------------------"									\
#	@echo " BUILD FINISHED "																	\
#	@echo "--------------------------------"									
#Link output files
$(OUTPUT).elf: $(OBJ_FILES) $(PROCESS_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(OUTPUT).elf -Wl,-Map,$(OUTPUT).map
#Create object files
$(PROCESS_FILES): %.e : %.c
	$(CC) -E $(CFLAGS) $< -o $@
$(OBJ_FILES): %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
#Create assembler file of a C source
%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@
#Loads the program to the avr device
load:
	avrdude -p $(MCU) -c $(PROG) -P $(PORT) -e -v -U flash:w:$(OUTPUT).hex
#Program fuses
fuses:
	avrdude -p $(MCU) -c $(PROG) -P $(PORT) -v -e -U lfuse:w:0x42:m -U hfuse:w:0x99:m -U efuse:w:0xff:m
read-fuses:
	avrdude -p $(MCU) -c $(PROG) -U lfuse:r:low_fuse_val.hex:h -U hfuse:r:high_fuse_val.hex:h
#flash:w:$(OUTPUT).hex
#Starts debugging
debug:
	avarice -2 -j $(PORT) $(DHOST):$(DPORT)
#Loads the program to the avr device and starts debugging
dload: $(OUTPUT).elf
	avarice -2 -j $(PORT) -e -p -f $(OUTPUT).elf $(DHOST):$(DPORT)
#Get information about memory usage
size: $(OUTPUT).elf
	avr-size -C --mcu=$(MCU) $(OUTPUT).elf
#Cleans all generated files
clean:
	rm -f $(OBJ_FILES)
	rm -f $(PROCESS_FILES)
	rm -f $(OUTPUT).elf
	rm -f $(OUTPUT).hex
	rm -f $(OUTPUT).map
