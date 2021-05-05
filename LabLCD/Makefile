# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

#all:shapemotion.elf

libLcd.a: lcdutils.o lcddraw.o
	$(AR) crs $@ $^
lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lin
	cp *.h ../h

#additional rules for files
shapemotion.elf: ${COMMON_OBJECTS} shapemotion.o wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lShape -lCircle -lp2sw

lcddemo2.elf: lcddemo2.o libLcd.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer

load1: shapemotion.elf
	msp430loader.sh $^

load2: lcddemo2.elf
	msp430loader.sh $^


clean:
	rm -f *.o *.elf *~
