#include "../include/endiannes.h"

int is_BigEndian() {
	unsigned int a = 0xAA0000FF;
	return (int)(((unsigned char *)&a)[0] == 0xAA);
}