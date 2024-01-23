CC=arm-none-eabi-gcc -g
CFLAGS=-mcpu=cortex-m3 -mthumb -nostdlib
CPPFLAGS=-DSTM32F103xB \
		 -Ivendor/CMSIS/CMSIS/Core/Include \
		 -Ivendor/CMSIS/Device/ST/cmsis_device_f1/Include 
LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE) -Wl,-Map=$(target)final.map

PROGRAMMER=openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f1x.cfg

TARGET_DIR = Build/Output/
OBJECT_DIR = Build/Objects/
SOURCE_DIR = Source/
F103_LIBRARY = F103_LIBRARY/

OBJ = $(OBJECT_DIR)main.o $(OBJECT_DIR)startup.o $(OBJECT_DIR)system_stm32f1xx.o $(OBJECT_DIR)GPIO.o $(OBJECT_DIR)Delay.o

all: $(TARGET_DIR)out.elf

$(TARGET_DIR)out.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ $^

$(OBJECT_DIR)main.o: $(SOURCE_DIR)main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -I$(F103_LIBRARY)

$(OBJECT_DIR)GPIO.o: $(F103_LIBRARY)GPIO.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -I$(F103_LIBRARY)

$(OBJECT_DIR)Delay.o: $(F103_LIBRARY)Delay.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -I$(F103_LIBRARY)

$(OBJECT_DIR)startup.o: $(SOURCE_DIR)startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

$(OBJECT_DIR)system_stm32f1xx.o: Vendor/CMSIS/Device/ST/cmsis_device_f1/Source/Templates/system_stm32f1xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

flash:	$(TARGET_DIR)out.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(TARGET_DIR)out.elf verify reset exit"

.PHONY: clean
clean:
	rm -f $(OBJECT_DIR)*.o $(OBJECT_DIR)*.s $(TARGET_DIR)*.elf $(TARGET_DIR)*.map