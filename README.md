# avr-udp
Simple UDP stack for AVR and the ENC28J60

This project is based on the [Tuxgraphics AVR web server](http://tuxgraphics.com/common/src2/article06111/).
However, there are large modified parts.

## How it works
This library does not keep any sort of dynamic ARP table.
Instead, all target IPs and MACs are hardcoded into the device.
The file network_config.c contains the configuration of the device and a list of other network devices which can be contacted:

	0x54,0x55,0x58,0x10,0x00,0x24, // MAC
	10, 0, 4, 7, // IP
	0x04, 0xb0, // port

Call ```udp_lib_send(buf, buflen, n);``` to send the buffer content to the n-th target in the list.
Call ```udp_lib_poll``` regularly. If a new UDP package arrived, it will call ```handle_udp(buf, buflen);``` with the content of the UDP package.
