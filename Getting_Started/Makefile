CC=arm-none-eabi-gcc -g
CFLAGS=-mcpu=cortex-m3 -mthumb -nostdlib
CPPFLAGS=-DSTM32F103xB \
		 -Ivendor/CMSIS/CMSIS/Core/Include \
		 -Ivendor/CMSIS/Device/ST/cmsis_device_f1/Include 
LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE) -Wl,-Map=$(target)final.map

PROGRAMMER=openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f1x.cfg

target = C:/Quan/Learning/Embedded/STM32_Low_Level/Getting_Started/Build/Output/
objects = C:/Quan/Learning/Embedded/STM32_Low_Level/Getting_Started/Build/Objects/
source = C:/Quan/Learning/Embedded/STM32_Low_Level/Getting_Started/Source/
F103_Library = C:/Quan/Learning/Embedded/STM32_Low_Level/Getting_Started/F103_Library/

all: $(target)out.elf

$(target)out.elf: $(objects)main.o $(objects)startup.o $(objects)system_stm32f1xx.o $(objects)GPIO.o $(objects)Delay.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ $^

$(objects)main.o: $(source)main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -I$(F103_Library)

$(objects)GPIO.o: $(F103_Library)GPIO.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -I$(F103_Library)

$(objects)Delay.o: $(F103_Library)Delay.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< -I$(F103_Library)

$(objects)startup.o: $(source)startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

$(objects)system_stm32f1xx.o: Vendor/CMSIS/Device/ST/cmsis_device_f1/Source/Templates/system_stm32f1xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

flash:	$(target)out.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $(target)out.elf verify reset exit"

.PHONY: clean
clean:
	rm -f $(objects)*.o $(objects)*.s $(target)*.elf $(target)*.map