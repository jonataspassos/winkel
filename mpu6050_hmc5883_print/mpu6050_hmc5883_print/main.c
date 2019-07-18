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
	float Q_angle = 0.003;
	float Q_gyro = 0.03;
	float R_angle = 0.23 * 0.23;
	float offset_x = 0;
	float offset_y = 0;
	float offset_z = 0;
	float XP_11 = 0.01, XP_12 = 0, XP_21 = 0, XP_22 = 0.01;
	float YP_11 = 0.01, YP_12 = 0, YP_21 = 0, YP_22 = 0.01;
	float ZP_11 = 0.01, ZP_12 = 0, ZP_21 = 0, ZP_22 = 0.01;
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
	
	int KalmanFilter(float Acc, float Gyro, float offset, float P_11, float P_12, float P_21, float P_22){
		
		float retorno[5];
		float KF_angulo;
		
		float y,S;
		float K_1,K_2;
		
		KF_angulo += deltaT*(Gyro-offset);		
		
		P_11 += -deltaT * (P_21+P_12) + P_22 * deltaT * deltaT * Q_angle * Q_angle;
		P_12 += -deltaT * P_22;
		P_21 += -deltaT * P_22;
		P_22 += Q_gyro * Q_gyro * deltaT;
		
		y= Acc - KF_angulo;
		S = P_11 + R_angle;
		K_1= P_11/S;
		K_2= P_21/S;
		
		KF_angulo += K_1 * y;
		offset += K_2 * y;
		
		
		//estrutura do vetor de retorno:
		retorno[0] = KF_angulo;
		retorno[1] = offset;		
		retorno[2] = P_11;
		retorno[3] = P_12;
		retorno[4] = P_21;
		retorno[5] = P_22;		
		return retorno;
	}
	
	float AccelX, AccelY, AccelZ, Temperatura, gyroX, gyroY, gyroZ;
	float magnetX, magnetY, magnetZ;
	float valores_X[5],valores_Y[5],valores_Z[5];
	
	
    USART_CONFIG();
	I2C_Inic();
	MPU6050_Inic();
	HMC5883L_Inic();
	
	_delay_ms(4000);
	
	
	
    while (1) {
		MPU6050_Read(&AccelX, &AccelY, &AccelZ, &Temperatura, &gyroX, &gyroY, &gyroZ);
		HMC5883L_Read(&magnetX,&magnetY,&magnetZ);

		float acc_sensibilty = 16384/10;
		float gyro_sensibilty = 131;
		float magnet_sensibility = 230;
		
		AccelX= (AccelX/acc_sensibilty);
		AccelY= (AccelY/acc_sensibilty);
		AccelZ= (AccelZ/acc_sensibilty);
		gyroX= (gyroX/acc_sensibilty);
		gyroY= (gyroY/acc_sensibilty);
		gyroZ= (gyroZ/acc_sensibilty);
		magnetX= (magnetX/acc_sensibilty);
		magnetY= (magnetY/acc_sensibilty);
		magnetZ= (magnetZ/acc_sensibilty);
		
		
		valores_X = KalmanFilter(AccelX,gyroX,offset_x,XP_11,XP_12,XP_21,XP_22);
		valores_Y = KalmanFilter(AccelY,gyroY,offset_y,YP_11,YP_12,YP_21,YP_11);
		valores_Z = KalmanFilter(AccelZ,gyroZ,offset_z,ZP_11,ZP_12,ZP_21,ZP_11);
		
		USART_TRANSFER_STRING("valores_X\t");
		USART_TRANSFER_STRING("\r\n");
		USART_TRANSFER_FLOAT(valores_X);
		USART_TRANSFER_STRING("\t");

		
		
		/*
		USART_TRANSFER_STRING("AccelX\t");
		USART_TRANSFER_STRING("AccelY\t");
		USART_TRANSFER_STRING("AccelZ\t");
		USART_TRANSFER_STRING("gyroX\t");
		USART_TRANSFER_STRING("gyroY\t");
		USART_TRANSFER_STRING("gyroZ\t");
		USART_TRANSFER_STRING("magnetX\t");
		USART_TRANSFER_STRING("magnetY\t");
		USART_TRANSFER_STRING("magnetZ");
		USART_TRANSFER_STRING("\r\n");
		USART_TRANSFER_INT((AccelX/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
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
		*/
		
		USART_TRANSFER_STRING("\r\n");
		
		
		
		//
		
    }
}

