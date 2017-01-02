/*********************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher 
 * Copyright: GPL V2
 *
 * IP/ARP/UDP/TCP functions
 *
 *********************************************/
//@{
#ifndef IP_ARP_UDP_TCP_H
#define IP_ARP_UDP_TCP_H
#include <avr/pgmspace.h>

#define DEST_MAC_FIELD 0
#define DEST_IP_FIELD DEST_MAC_FIELD+6
#define DEST_PORT_FIELD DEST_IP_FIELD+4
#define BUFFER_SIZE 450
extern uint8_t buf[BUFFER_SIZE+1];

extern uint8_t eth_type_is_arp_and_my_ip(uint16_t len);
extern uint8_t eth_type_is_ip_and_my_ip(uint16_t len);
extern void make_arp_answer_from_request(void);
extern void make_echo_reply_from_request(uint16_t len);


extern void init_len_info(void);
void send_udp(uint8_t *data, uint8_t datalen, uint8_t *dest_description);


#endif /* IP_ARP_UDP_TCP_H */
//@}
