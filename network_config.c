#include "lib/network_config.h"

uint8_t my_description[12] = {
	0x54,0x55,0x58,0x10,0x00,0x24,
//	192, 168, 178, 200,
	10, 0, 4, 7,
	0x04, 0xb0,
};

const uint8_t destinations[] PROGMEM = 
{
//	desktop
//	0xd0, 0x50, 0x99, 0x94, 0xdd, 0x73,
//	192, 168, 178, 34,

//	laptop
	0x00, 0x22, 0xfb, 0x63, 0x51, 0x18,
	10, 0, 0, 212,

	0x04, 0xb0
};
