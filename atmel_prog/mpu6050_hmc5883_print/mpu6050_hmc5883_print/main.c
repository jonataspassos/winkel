/*
 * mpu6050_hmc5883_print.c
 *
 * Created: 20/06/2019 02:15:48
 * Author : jonatas passero
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "../../atmel_libs/usart.h"
#include "../../atmel_libs/i2c.h"
#include "../../atmel_libs/mpu6050.h"
#include "../../atmel_libs/hmc5883l.h"


int main(void) {
	// DECLARAÇÃO DE VARIÁVEIS //
	
	float Q_angle = 0.003; //MATRIZ DE COVARIÂNCIA
	float Q_gyro = 0.03; //MATRIZ DE COVARIÂNCIA
	float R_angle = square(0.23); //COVARIÂNCIA DO ÂNGULO
	float offset_x = 0;
	float offset_y = 0;
	float offset_z = 0;
	float XP_11 = 0.01, XP_12 = 0, XP_21 = 0, XP_22 = 0.01;
	float YP_11 = 0.01, YP_12 = 0, YP_21 = 0, YP_22 = 0.01;
	float ZP_11 = 0.01, ZP_12 = 0, ZP_21 = 0, ZP_22 = 0.01;
	float deltaT = 0.05;
	
	float KanguloX;
	float KanguloY;
	float KanguloZ;
	
	typedef struct { //VARIÁVEL "PERSONALIZADA" PARA RETORNO DO FILTRO DE KALMAN
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
	
	// DEFINE FUNÇÃO DO FILTRO DE KALMAN //
	FKalman KalmanFilter(float Acc, float Gyro, float offset, float P_11, float P_12, float P_21, float P_22){
			
		float KF_angulo=0;
		float y,S;
		float K_1,K_2;
		
		KF_angulo += deltaT*(Gyro-offset);		
		
		P_11 += -deltaT * (P_21+P_12) + P_22 * square(deltaT) * square(Q_angle);
		P_12 += -deltaT * P_22;
		P_21 += -deltaT * P_22;
		P_22 += square(Q_gyro) * deltaT;
		
		y= Acc - KF_angulo;
		S = P_11 + R_angle;
		K_1= P_11/S;
		K_2= P_21/S;
		
		KF_angulo += K_1 * y;
		offset += K_2 * y;
		
		//P_11 -=K_1 * P_11;
		//P_12 -=K_1 * P_12;
		//P_21 -=K_2 * P_21;
		//P_22 -=K_2 * P_22;
		
		FKalman R;
		R = SetFKalman(KF_angulo,offset,P_11,P_12,P_21,P_22);
		return R;
	}
	
	
	
	int AccelX, AccelY, AccelZ, Temperatura, GyroX, GyroY, GyroZ;
	int MagnetX, MagnetY, MagnetZ;
	FKalman valores_X,valores_Y,valores_Z;
	
	
    USART_CONFIG();
	I2C_Inic();
	MPU6050_Inic();
	HMC5883L_Inic();
	
	_delay_ms(4000);
	
	
	
    while (1) { // LOOP DE EXECUÇÃO
		
		// COLETA DE DADOS MAGNETÔMETRO ACELERÔMETRO GIROSCÓIPIO //
		MPU6050_Read(&AccelX, &AccelY, &AccelZ, &Temperatura, &GyroX, &GyroY, &GyroZ);
		HMC5883L_Read(&MagnetX,&MagnetY,&MagnetZ);

		// SENSIBILIDADES (OBTIDAS POR DATASHEETS) //
		float acc_sensibilty = 16384/10;
		float gyro_sensibilty = 131;
		float magnet_sensibility = 1370;
		
		float sAccelX = AccelX/acc_sensibilty;
		float sAccelY = AccelY/acc_sensibilty;
		float sAccelZ = AccelZ/acc_sensibilty;
		
		float sGyroX = GyroX/gyro_sensibilty;
		float sGyroY = GyroY/gyro_sensibilty;
		float sGyroZ = GyroZ/gyro_sensibilty;
		
		float sMagnetX = MagnetX/magnet_sensibility;
		float sMagnetY = MagnetY/magnet_sensibility;
		float sMagnetZ = MagnetZ/magnet_sensibility;
		
		// CALCULO DOS ÂNGULOS DE EULER // 
		
		float Xangle = atan2(sAccelY,sAccelZ); //Roll??
		float Yangle = atan2(-sAccelX,sqrt(square(sAccelY)+square(sAccelZ))); //Pitch??	
		if (sAccelX < 0)
			Yangle += M_PI;
		float Zangle = atan2((sMagnetZ * sin(Xangle) - sMagnetY * cos(Xangle)),
						(sMagnetX * cos(Yangle) + sMagnetY * sin(Yangle) * 
						sin(Xangle) + sMagnetZ * sin(Yangle) * cos(Xangle))); // Yaw??
		
		Xangle += 2*M_PI;
		Yangle += 2*M_PI;
		Zangle += 2*M_PI;
		
		// CHAMADA DAS FUNÇÕES DO FILTRO DE KALMAN //
		valores_X = KalmanFilter(Xangle,sGyroX,offset_x,XP_11,XP_12,XP_21,XP_22);
		KanguloX=valores_X.K;
		offset_x=valores_X.O;
		XP_11=valores_X.P1;
		XP_12=valores_X.P2;
		XP_21=valores_X.P3;
		XP_22=valores_X.P4;
		
		/*USART_TRANSFER_FLOAT(sAccelX);
		USART_TRANSFER_STRING("\n");*/
		
		
		/*USART_TRANSFER_STRING("2:");
		USART_TRANSFER_FLOAT(KanguloX);
		USART_TRANSFER_STRING("\n");
		_delay_ms(100);*/
		
		valores_Y = KalmanFilter(Yangle,sGyroY,offset_y,YP_11,YP_12,YP_21,YP_22);
		KanguloY=valores_Y.K;
		offset_y=valores_Y.O;
		YP_11=valores_Y.P1;
		YP_12=valores_Y.P2;
		YP_21=valores_Y.P3;
		YP_22=valores_Y.P4;
		
		/*USART_TRANSFER_STRING("1:");
		USART_TRANSFER_FLOAT(KanguloY);
		USART_TRANSFER_STRING("\n");
		_delay_ms(100);*/
		
		valores_Z = KalmanFilter(Zangle,sGyroZ,offset_z,ZP_11,ZP_12,ZP_21,ZP_22);
		KanguloZ=valores_Z.K;
		offset_z=valores_Z.O;
		ZP_11=valores_Z.P1;
		ZP_12=valores_Z.P2;
		ZP_21=valores_Z.P3;
		ZP_22=valores_Z.P4;
		
		/*USART_TRANSFER_STRING("3:");
		USART_TRANSFER_FLOAT(KanguloZ);
		_delay_ms(100);
		USART_TRANSFER_STRING("\r\n");*/
		
		// IMPRESSÃO DOS DADOS //
		
		USART_TRANSFER_STRING("1:");
		USART_TRANSFER_FLOAT(KanguloY);
		USART_TRANSFER_STRING("\n");
		USART_TRANSFER_STRING("\r\n");
		
		
		
		
		
		
    }
}

