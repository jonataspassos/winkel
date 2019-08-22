#ifndef BMP180_H
#define BMP180_H

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <repository/i2c.h>
#include <util/delay.h>

#define BMP180_ADDRESS 0xEE
#define BMP180_RA_TEMP 0x2E
#define BMP180_RA_PRES_0 0x34
#define BMP180_RA_PRES_1 0x74
#define BMP180_RA_PRES_2 0xB4
#define BMP180_RA_PRES_3 0xF4

void BMP180_Inic(){
}

void BMP180_Read(){
}

#endif