# makefile, written by guido socher
# edited by Klaus Neuschwander (hephaisto)


CC=avr-gcc
OBJCOPY=avr-objcopy
# optimize for size:
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues -DF_CPU=$(F_CPU)

enc28j60.o : enc28j60.c avr_compat.h timeout.h enc28j60.h
	$(CC) $(CFLAGS) -Os -c enc28j60.c

ip_arp_udp_tcp.o : ip_arp_udp_tcp.c net.h avr_compat.h enc28j60.h
	$(CC) $(CFLAGS) -Os -c ip_arp_udp_tcp.c

main.o : main.c ip_arp_udp_tcp.h avr_compat.h enc28j60.h timeout.h net.h
	$(CC) $(CFLAGS) -Os -c main.c

udp_lib.o : udp_lib.c udp_lib.h ip_arp_udp_tcp.h
	$(CC) $(CFLAGS) -Os -c $<

clean:
	rm -f *.o
