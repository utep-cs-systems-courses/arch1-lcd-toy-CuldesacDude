# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include/-L../lib

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c
AR		= msp430-elf-ar

all: toy.elf

#additional rules for files
toy.elf: ${COMMON_OBJECTS} p2_interrupt_handler.o switches.o main.o buzzer.o stateMachines.o led.o wdt_handler.o asPeriod.o shape.o compare.o sirenStateAdvance.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: toy.elf
	msp430loader.sh toy.elf

clean:
	rm -f *.o *.elf *~

led.o: led.h

shape.o: shape.h

stateMachines.o: led.h buzzer.h stateMachines.h

buzzer.o: buzzer.h

switches.o:  switches.h led.h stateMachines.h buzzer.h

p2_interrupt_handler.o: switches.h
