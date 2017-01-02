#include "network_config.h"
#include "udp_lib.h"

uint8_t response_data[9]="it worx!";

void handle_udp(uint8_t *buf, uint8_t len)
{
	if (buf[0]=='t' && len==5)
		udp_lib_send(response_data, 9, 0);
}

int main(void)
{
	udp_lib_init();

	while(1)
	{
		udp_lib_poll();
	}
	return (0);
}

