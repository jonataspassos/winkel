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
	
	float KalmanX;
	int KalmanY;
	int KalmanZ;
	
	typedef struct {
		float K,O,P1,P2,P3,P4;
	} FKalman ;
	
	FKalman SetFKalman (float K, float O, float P1, float P2, float P3, float P4)
	{
		FKalman R;
		R.K =K;
		R.O=O;
		R.P1=P1;
		R.P2=P2;
		R.P3=P3;
		R.P4=P4;
		return R;
	}

	FKalman KalmanFilter(float Acc, float Gyro, float offset, float P_11, float P_12, float P_21, float P_22){
			
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
		
		
		FKalman R;
		R = SetFKalman(KF_angulo,offset,P_11,P_12,P_21,P_22);
		return R;
	}
	
	int AccelX, AccelY, AccelZ, Temperatura, gyroX, gyroY, gyroZ;
	int magnetX, magnetY, magnetZ;
	FKalman valores_X,valores_Y,valores_Z;
	
	
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
		int magnet_sensibility = 230;
		
		
		 valores_X = KalmanFilter(AccelX/acc_sensibilty,gyroX/gyro_sensibilty,offset_x,XP_11,XP_12,XP_21,XP_22);
		KalmanX=valores_X.K;
		offset_x=valores_X.O;
		XP_11=valores_X.P1;
		XP_12=valores_X.P2;
		XP_21=valores_X.P3;
		XP_22=valores_X.P4;
		valores_Y = KalmanFilter(AccelY/acc_sensibilty,gyroY/gyro_sensibilty,offset_y,YP_11,YP_12,YP_21,YP_11);
		KalmanY=valores_Y.K;
		offset_y=valores_Y.O;
		YP_11=valores_Y.P1;
		YP_12=valores_Y.P2;
		YP_21=valores_Y.P3;
		YP_22=valores_Y.P4;
		valores_Z = KalmanFilter(AccelZ/acc_sensibilty,gyroZ/gyro_sensibilty,offset_z,ZP_11,ZP_12,ZP_21,ZP_11);
		KalmanZ=valores_Z.K;
		offset_z=valores_Z.O;
		ZP_11=valores_Z.P1;
		ZP_12=valores_Z.P2;
		ZP_21=valores_Z.P3;
		ZP_22=valores_Z.P4;
		
		/*
		//TESTE EM X
		USART_TRANSFER_STRING("AccelX\t");
		USART_TRANSFER_STRING("gyroX\t");
		USART_TRANSFER_STRING("Valores_X\t");
		USART_TRANSFER_STRING("\r\n");
		USART_TRANSFER_INT((AccelX/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((gyroX/gyro_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_FLOAT(KalmanX);
		USART_TRANSFER_STRING("\t"); */
		
		
		//TESTE EM Y
		USART_TRANSFER_STRING("AccelY\t");
		USART_TRANSFER_STRING("gyroY\t");
		USART_TRANSFER_STRING("Valores_Y\t");
		USART_TRANSFER_STRING("\r\n");
		USART_TRANSFER_INT((AccelY/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((gyroY/gyro_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_FLOAT(KalmanY);
		USART_TRANSFER_STRING("\t"); 
		
		/*
		//TESTE EM Z
		USART_TRANSFER_STRING("AccelZ\t");
		USART_TRANSFER_STRING("gyroZ\t");
		USART_TRANSFER_STRING("Valores_Z\t");
		USART_TRANSFER_STRING("\r\n");
		USART_TRANSFER_INT((AccelZ/acc_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_INT((gyroZ/gyro_sensibilty)*100);
		USART_TRANSFER_STRING("\t");
		USART_TRANSFER_FLOAT(KalmanZ);
		USART_TRANSFER_STRING("\t"); 
		*/


		
		
		
		/*USART_TRANSFER_STRING("AccelX\t");
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
		USART_TRANSFER_INT((magnetZ/magnet_sensibility)*100);*/
		
		
		USART_TRANSFER_STRING("\r\n");
		
		
		
		//
		
    }
}

