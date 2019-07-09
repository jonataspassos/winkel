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


int main(void) {
	//float Q_angle = 0.003;
	//float Q_gyro = 0.03;
	float R_angle = 0.23 * 0.23;
	float offset_x = 0;
	float offset_y = 0;
	float offset_z = 0;
	float XP_00 = 0.01, XP_01 = 0, XP_10 = 0, XP_11 = 0.01;
	float YP_00 = 0.01, YP_01 = 0, YP_10 = 0, YP_11 = 0.01;
	float ZP_00 = 0.01, ZP_01 = 0, ZP_10 = 0, ZP_11 = 0.01;
	float KF_anguloX = 0.0;
	float KF_anguloY = 0.0;
	float KF_anguloZ = 0.0;
	float deltaT = 0.05;
	float rate_gyr_x = 0;
	float rate_gyr_y = 0;
	float rate_gyr_z = 0;
	float AccZangle = 0;
	float th1 = 0;
	float th2 = 0;
	float th3 = 0;
	
	int KalmanFilter(int Acc,Gyro,offset,P_00,P_01,P_10,P_11){
		int y,S;
		int K_1,K_2;
		
		KF_angulo += deltaT*(gyro-offset);		
		return (KF_angulo)
	}
	
	/*
	KF_anguloX= KalmanFilter(AccelX,gyroX,offset_x,XP_00,XP_01,XP_10,XP_11)
	KF_anguloY= KalmanFilter(AccelY,gyroY,offset_y,YP_00,YP_01,YP_10,YP_11)
	KF_anguloZ= KalmanFilter(AccelZ,gyroZ,offset_z,ZP_00,ZP_01,ZP_10,ZP_11)
	*/
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
	
    while (1) {
		MPU6050_Read(&AccelX, &AccelY, &AccelZ, &Temperatura, &gyroX, &gyroY, &gyroZ);
		HMC5883L_Read(&magnetX,&magnetY,&magnetZ);

		int acc_sensibilty = 16384/10;
		int gyro_sensibilty = 131;
		int magnet_sensibility = 230;
		
		//AccelX = AccelX/acc_sensibilty;
		
		
		
		USART_TRANSFER_INT((AccelX/acc_sensibilty)*100);
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

