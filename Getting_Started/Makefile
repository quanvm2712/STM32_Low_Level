CC=arm-none-eabi-gcc -g
CFLAGS=-mcpu=cortex-m3 -mthumb -nostdlib
CPPFLAGS=-DSTM32F103xB \
		 -Ivendor/CMSIS/CMSIS/Core/Include \
		 -Ivendor/CMSIS/Device/ST/cmsis_device_f1/Include 
LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)	

PROGRAMMER=openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f1x.cfg


all: build

build: main.o startup.o system_stm32f1xx.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $^ -o blink.elf 

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

system_stm32f1xx.o: vendor/CMSIS/Device/ST/cmsis_device_f1/Source/Templates/system_stm32f1xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) vendor/CMSIS/Device/ST/cmsis_device_f1/Source/Templates/system_stm32f1xx.c -c

flash:	blink.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"

.PHONY: clean
clean:
	rm -f *.o *.elf *.s