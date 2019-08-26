#ifndef HMC5883L_H
#define HMC5883L_H
#include "usart.h"
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include "i2c.h"
#include <util/delay.h>

#define HMC5883L_ADDRESS 0x3c
#define HMC5883L_RA_CONFA 0x00
#define HMC5883L_RA_CONFB 0x01
#define HMC5883L_RA_MODE 0x02
#define HMC5883L_RA_MAGNET_XOUT_H 0x03
#define HMC5883L_RA_MAGNET_XOUT_L 0x04
#define HMC5883L_RA_MAGNET_YOUT_H 0x05
#define HMC5883L_RA_MAGNET_YOUT_L 0x06
#define HMC5883L_RA_MAGNET_ZOUT_H 0x07
#define HMC5883L_RA_MAGNET_ZOUT_L 0x08
#define HMC5883L_RA_STATUS 0x09
#define HMC5883L_RA_ID_A 0x0A
#define HMC5883L_RA_ID_B 0x0B
#define HMC5883L_RA_ID_C 0x0C

void HMC5883L_Inic(){
	_delay_ms(1);
	I2C_SetRegisterSlave(HMC5883L_ADDRESS,HMC5883L_RA_CONFA,0x10);
	
	_delay_ms(1);
	I2C_PRINT_IF_NOT_OK(I2C_SetRegisterSlave(HMC5883L_ADDRESS,HMC5883L_RA_CONFB,0x00));
	_delay_ms(1);
	I2C_PRINT_IF_NOT_OK(I2C_SetRegisterSlave(HMC5883L_ADDRESS,HMC5883L_RA_MODE,0x00));
	_delay_ms(1);
}

void HMC5883L_Read(int *MagnetX, int *MagnetY, int *MagnetZ){
	I2C_Start();
	I2C_Send( HMC5883L_ADDRESS | I2C_WRITE);
	I2C_Send( HMC5883L_RA_MAGNET_XOUT_H );
	_delay_ms(20);
	I2C_Start();
	
	I2C_Send( HMC5883L_ADDRESS | I2C_READ );
	*MagnetX = (I2C_ReciveACK() << 8) | I2C_ReciveACK();
	*MagnetY = (I2C_ReciveACK() << 8) | I2C_ReciveACK();
	*MagnetZ = (I2C_ReciveACK() << 8) | I2C_ReciveNACK();
	I2C_Stop();
}

#endif