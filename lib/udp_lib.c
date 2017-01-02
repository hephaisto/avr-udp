#include "enc28j60.h"
#include "network_config.h"
#include "ip_arp_udp_tcp.h"
#include "timeout.h"
#include "net.h"
#include "udp_lib.h"

void udp_lib_init(void)
{
	/*initialize enc28j60*/
	enc28j60Init(my_description+DEST_MAC_FIELD);
	enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
	_delay_loop_1(50); // 12ms

	/* Magjack leds configuration, see enc28j60 datasheet, page 11 */
	// LEDB=yellow LEDA=green
	//
	// 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
	// enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
	enc28j60PhyWrite(PHLCON,0x476);
	_delay_loop_1(50); // 12ms
}

void udp_lib_poll(void)
{
	uint16_t plen;
	uint8_t payloadlen=0;

	// get the next new packet:
	plen = enc28j60PacketReceive(BUFFER_SIZE, buf);

	/*plen will ne unequal to zero if there is a valid 
	 * packet (without crc error) */
	if(plen==0){
		return;
	}
	// arp is broadcast if unknown but a host may also
	// verify the mac address by sending it to 
	// a unicast address.
	if(eth_type_is_arp_and_my_ip(plen)){
		make_arp_answer_from_request();
		return;
	}
	// check if ip packets (icmp or udp) are for us:
	if(eth_type_is_ip_and_my_ip(plen)==0){
		return;
	}

	if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
		// a ping packet, let's send pong
		make_echo_reply_from_request(plen);
		return;
	}
	// udp interface:
	if (buf[IP_PROTO_P]==IP_PROTO_UDP_V){
		if(buf[UDP_DST_PORT_H_P] == my_description[DEST_PORT_FIELD] && buf[UDP_DST_PORT_L_P] == my_description[DEST_PORT_FIELD+1])
		{
			payloadlen=buf[UDP_LEN_L_P]-UDP_HEADER_LEN;
			handle_udp(buf+UDP_DATA_P, payloadlen);
		}
	}
}

void udp_lib_send(uint8_t *data, uint8_t datalen, uint8_t destination_ID)
{
	uint8_t destination[12];
	memcpy_P(destination, destinations+12*destination_ID, 12);
	send_udp(data, datalen, destination);
}
