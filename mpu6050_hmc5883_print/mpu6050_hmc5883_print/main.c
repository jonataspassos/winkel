/*
 * mpu6050_hmc5883_print.c
 *
 * Created: 20/06/2019 02:15:48
 * Author : jonatas passero
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../atmel_libs/usart.h"
#include "../../atmel_libs/i2c.h"
#include "../../atmel_libs/mpu6050.h"
#include "../../atmel_libs/hmc5883l.h"


int main(void)
{
	int AccelX, AccelY, AccelZ, Temperatura, gyroX, gyroY, gyroZ;
	int magnetX, magnetY, magnetZ;
	
    USART_CONFIG();
	I2C_Inic();
	MPU6050_Inic();
	HMC5883L_Inic();
	
	_delay_ms(4000);
	
	/*USART_TRANSFER_STRING("AccelX\t");
	USART_TRANSFER_STRING("AccelY\t");
	USART_TRANSFER_STRING("AccelZ\t");
	USART_TRANSFER_STRING("gyroX\t");
	USART_TRANSFER_STRING("gyroY\t");
	USART_TRANSFER_STRING("gyroZ\t");*/
	USART_TRANSFER_STRING("magnetX\t");
	USART_TRANSFER_STRING("magnetY\t");
	USART_TRANSFER_STRING("magnetZ");
	USART_TRANSFER_STRING("\r\n");
	
    while (1) 
    {
		MPU6050_Read(&AccelX, &AccelY, &AccelZ, &Temperatura, &gyroX, &gyroY, &gyroZ);
		HMC5883L_Read(&magnetX,&magnetY,&magnetZ);

		int acc_sensibilty = 16384/10;
		int gyro_sensibilty = 131;
		int magnet_sensibility = 230;
		
		//AccelX = AccelX/acc_sensibilty;
		
		
		
		/*USART_TRANSFER_INT((AccelX/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((AccelY/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((AccelZ/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((gyroX/gyro_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((gyroY/gyro_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((gyroZ/gyro_sensibilty)*100);
		USART_TRANSFER_STRING("\t");*/
		USART_TRANSFER_INT(magnetX);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT(magnetY);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT(magnetZ);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((magnetX/magnet_sensibility)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((magnetY/magnet_sensibility)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((magnetZ/magnet_sensibility)*100);
		
		
		USART_TRANSFER_STRING("\r\n");
		
		
		
		//
		
    }
}

