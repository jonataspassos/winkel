#ifndef SERIAL_PRINTER_H
#define SERIAL_PRINTER_H
#include <avr/io.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
    void USART_CONFIG();
    void USART_TRANSFER(uint8_t ender);
    void USART_TRANSFER_STRING(char * text);
    void USART_TRANSFER_INT(long int val);
    void USART_TRANSFER_INT_HEX(long int val);
	void USART_CONFIG(){
	UCSR0A = 0x40;
	UCSR0B = 0x08;
	UCSR0C = 0x06;
	UBRR0L = 103;
	UBRR0H = 0;
}

void USART_TRANSFER(uint8_t ender){
	while((UCSR0A & 0x20)!=0x20){}
	UDR0 = ender;
}

void USART_TRANSFER_STRING(char * text){
	int i=0;
	while(text[i]){
		USART_TRANSFER(text[i]);
		i++;
	}
	//USART_TRANSFER(10);
	//USART_TRANSFER(13);
}

/*uint8_t USART_printf(const char * _format,...){
	va_list arg;
	int n;
	char c[30];
	va_start(arg,_format);
	n = sprintf(c,_format,arg);
	USART_TRANSFER_STRING(c);
	return n;
}*/

void USART_TRANSFER_INT(long int val){
	char text[20];
	int i=18;
	do{
		text[i] = ((char)val%10)+'0';
		val/=10;
		i--;
	}while(val && (i>=2));
	text[19] = 0;
	USART_TRANSFER_STRING(text+i+1);
}

void USART_TRANSFER_INT_HEX(long int val){
	char text[20];
	int i=18;
	char temp;
	do{
		temp = (char)val%16;
		if(temp<10)
			text[i] = temp+'0';
		else
			text[i] = temp+'A'-10;
		val/=16;
		i--;
	}while(val && (i>=2));
	text[19] = 0;
	text[i--] = 'x';
	text[i] = '0';
	USART_TRANSFER_STRING(text+i);
}
int mul(int x, int y){
	int z=0;
	for(;y>0;y--){
		z+=x;
	}
	for(;y<0;y++){
		z-=x;
	}
	return z;
}

int pot(int x, int y){
	int z;
	for(z=1;y>0;y--){
		z= mul(z,x);
		USART_TRANSFER_INT(z);
		USART_TRANSFER_STRING("\n");
	}
	return z;
}

void USART_TRANSFER_FLOAT(float val){
	char text[20];
	/*int temp = (int)((val - (int)val)*pot(10,precision));
	USART_TRANSFER_INT((int)((val - (int)val)));
	USART_TRANSFER_STRING("\r\n");
	USART_TRANSFER_INT(temp);
	USART_TRANSFER_STRING("\r\n");
	USART_TRANSFER_INT(pot(10,precision));
	USART_TRANSFER_STRING("\r\n");
	text[18-precision]='.';
	int i = 18;
	do{
		text[i] = ((char)temp%10)+'0';
		temp/=10;
		i--;
	}while(temp  && (i>=2));
	temp = (int)val;
	i = 18-precision-1;
	do{
		text[i] = ((char)temp%10)+'0';
		temp/=10;
		i--;
	}while(temp  && (i>=2));
	text[19] = 0;*/
	sprintf(text,"%09.3f",val);
	USART_TRANSFER_STRING(text);//+i+1
}
#endif