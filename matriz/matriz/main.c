/*
 * matriz.c
 *
 * Created: 20/06/2019 12:39:28
 * Author : jonatas passero
 */ 
#include <avr/io.h>
#include "../../atmel_libs/usart.h"
#include "../../atmel_libs/matriz.h"


int main(void)
{
	USART_CONFIG();
	Matriz * mat = MATRIZ_CREATE(LINHA,COLUNA,'i');
	Matriz * mat2 = MATRIZ_CREATE(COLUNA,LINHA,'f');
	Matriz * mat3 = NULL;
	int i;
	ElType temp;
	temp.f = 3;
	for(i=0;i<LINHA*COLUNA;i++){
		MATRIZ_EL(mat,i/COLUNA,i%COLUNA)->i = i;
		MATRIZ_EL(mat2,i%COLUNA,i/COLUNA)->f = i;
	}
	MATRIZ_PRINT(mat);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_PRINT(mat2);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_PRINT(mat3);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_SUM(&mat3,mat,mat2);
	MATRIZ_PRINT(mat3);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_MUL_ESCAL(&mat3,mat,temp,'f');
	MATRIZ_PRINT(mat3);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_MUL(&mat3,mat,mat2);
	MATRIZ_PRINT(mat3);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_TRANS(&mat3,mat2);
	MATRIZ_PRINT(mat3);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_FREE(&mat);
	MATRIZ_FREE(&mat2);
	MATRIZ_FREE(&mat3);
	
	MATRIZ_PRINT(mat);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_PRINT(mat2);
	USART_TRANSFER_STRING("\r\n");
	
	MATRIZ_PRINT(mat3);
	USART_TRANSFER_STRING("\r\n");
	
    while (1) 
    {
    }
}


