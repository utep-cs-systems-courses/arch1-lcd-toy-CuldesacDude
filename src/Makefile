# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:Game.elf

#additional rules for files
Game.elf: ${COMMON_OBJECTS} Game.o assemSound.o wdt_handler.o main.o switches.o stateMachines.o buzzer.o led.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lLcd -lShape -lCircle -lp2sw

load: Game.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~

#assemSound.o: assemSound.s
led.o: led.h
wdInterruptHandler.o: stateMachines.h buzzer.h led.h switches.h
stateMachines.o: led.h buzzer.h stateMachines.h
buzzer.o: buzzer.h
switches.o:  switches.h led.h stateMachines.h buzzer.h
p2_interrupt_handler.o: switches.h
