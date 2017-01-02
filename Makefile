.PHONY: example all lib

# device config
MCU=atmega328p
DUDE_MCU=atmega328p
DUDE_BAUD=57600
DUDE_PORT=/dev/ttyUSB0
DUDE_PROGRAMMER=arduino
F_CPU=16000000L
# end config

CC=avr-gcc
OBJCOPY=avr-objcopy
# optimize for size:
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues -DF_CPU=$(F_CPU)

all: lib example.hex
	@echo "done"

test: network_config.c
	udpcom/unix/udpcom test 10.0.4.7

lib:
	$(MAKE) -C lib

example: example.hex
	@echo "done"

example.hex : example.out 
	$(OBJCOPY) -R .eeprom -O ihex example.out example.hex 
	avr-size example.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
example.out : example.o lib/enc28j60.o lib/ip_arp_udp_tcp.o network_config.o lib/udp_lib.o
	$(CC) $(CFLAGS) -o example.out -Wl,-Map,example.map $^

example.o : example.c lib/ip_arp_udp_tcp.h lib/avr_compat.h lib/enc28j60.h lib/timeout.h lib/net.h
	$(CC) $(CFLAGS) -Os -Ilib -c example.c

load_example: example.hex
	$(LOADCMD) $(LOADARG)example.hex

network_config.o: network_config.c network_config.h
	$(CC) $(CFLAGS) -Os -Ilib -c $<


LOADCMD=avrdude
LOADARG=-p $(DUDE_MCU) -b $(DUDE_BAUD) -P $(DUDE_PORT) -c $(DUDE_PROGRAMMER) -e -U flash:w:


clean:
	rm -f *.o *.map *.out *.hex
