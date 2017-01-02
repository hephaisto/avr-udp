#include <inttypes.h>

void udp_lib_poll(void);
void udp_lib_init(void);

void udp_lib_send(uint8_t *data, uint8_t datalen, uint8_t destination_ID);
void handle_udp(uint8_t *buf, uint8_t len);
