CC=arm-none-eabi-gcc -g --specs=nosys.specs -nostartfiles -O0
CFLAGS=-mcpu=cortex-m3 -mthumb -Wall
CPPFLAGS=-DSTM32F103xB \
		 -Ivendor/CMSIS/CMSIS/Core/Include \
		 -Ivendor/CMSIS/Device/ST/cmsis_device_f1/Include \
		 -ISource/F103_LIBRARY/ \
		 -ISource/Hardware_Library/ \

LINKER_FILE=linker_script.ld 
LDFLAGS=-T $(LINKER_FILE) -Wl,-Map=Build/Output/final.map

PROGRAMMER=openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f1x.cfg

TARGET_DIR = Build/Output/
OBJECT_DIR = Build/Objects/
SOURCE_DIR = Source/
F103_LIBRARY_DIR = Source/F103_Library/
HARDWARE_LIBRARY_DIR = Source/Hardware_Library/

# List of source files
SRC := $(wildcard $(SOURCE_DIR)*.c)
F103_LIBRARY := $(wildcard $(F103_LIBRARY_DIR)*.c)
HARDWARE_LIBRARY := $(wildcard $(HARDWARE_LIBRARY_DIR)*.c)

# Generate the list of object files from source files
OBJ := 	$(patsubst $(SOURCE_DIR)%.c, $(OBJECT_DIR)%.o, $(SRC))
OBJ1 := $(patsubst $(F103_LIBRARY_DIR)%.c, $(OBJECT_DIR)%.o, $(F103_LIBRARY))
OBJ2 := $(patsubst $(HARDWARE_LIBRARY_DIR)%.c, $(OBJECT_DIR)%.o, $(HARDWARE_LIBRARY))

all: $(TARGET_DIR)out.elf

$(TARGET_DIR)out.elf: $(OBJ) $(OBJ2) $(OBJ1)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

$(OBJECT_DIR)%.o: $(SOURCE_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIR)%.o: $(F103_LIBRARY_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJECT_DIR)%.o: $(HARDWARE_LIBRARY_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

flash:	$(TARGET_DIR)out.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(TARGET_DIR)out.elf verify reset exit"

.PHONY: clean
clean:
	rm -f $(OBJECT_DIR)*.o $(OBJECT_DIR)*.s $(TARGET_DIR)*.elf $(TARGET_DIR)*.map