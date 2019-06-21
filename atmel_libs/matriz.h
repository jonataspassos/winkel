#ifndef MATRIZ_H
#define MATRIZ_H
#include <avr/io.h>
#include <stdlib.h>
#include "../../atmel_libs/usart.h"
#include <stdio.h>

#define LINHA 4
#define COLUNA 4

typedef union tp_el_type{
	float		f;
	long int	i;
}ElType;
typedef struct tp_matriz{
	ElType * el;
	int m;//linha
	int n;//coluna
	char type;// i para inteiro e f para flutuante
}Matriz;
Matriz * MATRIZ_CREATE(int m, int n, char type){
	if(m>0 && n>0 && (type=='i' || type == 'f')){
		Matriz *matriz = (Matriz *)malloc(sizeof(Matriz));
		matriz->m = m;
		matriz->n = n;
		matriz->type = type;
		matriz->el = (ElType *)calloc(m*n,sizeof(ElType));
		return matriz;
	}
	return NULL;
}
ElType * MATRIZ_EL(Matriz *mat, int i, int j){
	if(mat){
		return &((mat->el)[i*(mat->n)+j]);
	}
	return NULL;
}
void MATRIZ_SET_EL(Matriz *mat, int i, int j, ElType val){
	if(mat)
	*MATRIZ_EL(mat,i,j) = val;
}
ElType MATRIZ_GET_EL(Matriz *mat, int i, int j){
	ElType r;
	r.i = 0;
	if(mat){
		r = *MATRIZ_EL(mat,i,j);
	}
	return r;
}
void MATRIZ_PRINT_EL(Matriz *mat, int i, int j){
	if(mat){
		switch(mat->type){
			case 'i':USART_TRANSFER_INT(MATRIZ_EL(mat,i,j)->i );break;
			case 'f':USART_TRANSFER_FLOAT(MATRIZ_EL(mat,i,j)->f);break;
		}
	}
}
void MATRIZ_PRINT(Matriz *mat){
	if(mat){
		int i,j;
		char text[30];
		sprintf(text,"M: %d; N: %d; Type: %s \r\n",mat->m,mat->n,mat->type=='f'?"Float":"Int");
		USART_TRANSFER_STRING(text);
		for(i=0;i<mat->m;i++){
			USART_TRANSFER_STRING("|");
			for(j=0;j<mat->n;j++){
				USART_TRANSFER_STRING("\t");
				MATRIZ_PRINT_EL(mat,i,j);
			}
			USART_TRANSFER_STRING("\t|\r\n");
		}
		}else{
		USART_TRANSFER_STRING("Matriz Nula\r\n");
	}
	
}
void MATRIZ_FREE(Matriz **mat){
	if(*mat){
		free((*mat)->el);
		free(*mat);
		*mat = NULL;
	}
}
void MATRIZ_CONVERT(Matriz *mat, char type){
	if(mat){
		char old = mat->type;
		int i,j;
		mat->type = type;
		switch(mat->type){
			case 'i':
			switch(old){
				case 'f':
				for(i=0;i<mat->m;i++)
				for(j=0;j<mat->n;j++)
				MATRIZ_EL(mat,i,j)->i = (long int)MATRIZ_EL(mat,i,j)->f;
				break;
			}
			break;
			case 'f':
			switch(old){
				case 'i':
				for(i=0;i<mat->m;i++)
				for(j=0;j<mat->n;j++)
				MATRIZ_EL(mat,i,j)->f = (float)MATRIZ_EL(mat,i,j)->i;
				break;
			}
			break;
		}
	}
	return;
}
ElType EL_SUM(ElType a, ElType b, char type_a, char type_b, char type_c){
	ElType r;
	r.i = 0;
	switch(type_c){
		case 'i':
		r.i=0;
		switch(type_a){
			case 'i':r.i += a.i;break;
			case 'f':r.i += (int)a.f;break;
		}
		switch(type_b){
			case 'i':r.i += b.i;break;
			case 'f':r.i += (int)b.f;break;
		}
		return r;
		case 'f':
		r.i=0;
		switch(type_a){
			case 'i':r.f += a.i;break;
			case 'f':r.f += (int)a.f;break;
		}
		switch(type_b){
			case 'i':r.f += b.i;break;
			case 'f':r.f += (int)b.f;break;
		}
		return r;
	}
	return r;
}
ElType EL_MUL(ElType a, ElType b, char type_a, char type_b, char type_c){
	ElType r;
	r.i = 0;
	switch(type_c){
		case 'i':
		r.i=1;
		switch(type_a){
			case 'i':r.i *= a.i;break;
			case 'f':r.i *= (int)a.f;break;
		}
		switch(type_b){
			case 'i':r.i *= b.i;break;
			case 'f':r.i *= (int)b.f;break;
		}
		return r;
		case 'f':
		r.f=1;
		switch(type_a){
			case 'i':r.f *= a.i;break;
			case 'f':r.f *= (int)a.f;break;
		}
		switch(type_b){
			case 'i':r.f *= b.i;break;
			case 'f':r.f *= (int)b.f;break;
		}
		return r;
	}
	return r;
}
Matriz * MATRIZ_SUM(Matriz**matr, Matriz *mat1, Matriz *mat2){
	MATRIZ_FREE(matr);
	if(mat1 && mat2 && mat1->m == mat2->m && mat1->n == mat2->n){
		int i,j;
		*matr = MATRIZ_CREATE(mat1->m,mat1->n,mat1->type == 'f' || mat2->type =='f'?'f':'i');
		for(i=0;i<(*matr)->m;i++)
		for(j=0;j<(*matr)->n;j++)
		*MATRIZ_EL((*matr),i,j) = EL_SUM(*MATRIZ_EL(mat1,i,j),*MATRIZ_EL(mat2,i,j),mat1->type,mat2->type,(*matr)->type);
		return *matr;
	}
	return NULL;
}
Matriz * MATRIZ_MUL_ESCAL(Matriz ** matr, Matriz*mat1,ElType es,char type){
	int i,j;
	MATRIZ_FREE(matr);
	if(mat1){
		*matr = MATRIZ_CREATE(mat1->m,mat1->n,mat1->type == 'f' || type =='f'?'f':'i');
		for(i=0;i<(*matr)->m;i++)
		for(j=0;j<(*matr)->n;j++)
		*MATRIZ_EL(*matr,i,j) = EL_MUL(*MATRIZ_EL(mat1,i,j),es,mat1->type,type,(*matr)->type);
		return *matr;
	}
	return NULL;
}
Matriz * MATRIZ_MUL(Matriz** matr, Matriz *mat1, Matriz *mat2){
	MATRIZ_FREE(matr);
	if(mat1 && mat2 && mat1->n == mat2->m){
		int i,j,k;
		*matr = MATRIZ_CREATE(mat1->m,mat2->n,mat1->type == 'f' || mat2->type =='f'?'f':'i');
		for(i=0;i<(*matr)->m;i++)
		for(j=0;j<(*matr)->n;j++){
			MATRIZ_EL(*matr,i,j)->i=0;
			for(k=0;k<mat1->n;k++){
				*MATRIZ_EL(*matr,i,j) = EL_SUM(*MATRIZ_EL(*matr,i,j),
				EL_MUL(*MATRIZ_EL(mat1,i,k),*MATRIZ_EL(mat2,k,j),
				mat1->type,mat2->type,(*matr)->type),
				(*matr)->type, (*matr)->type,(*matr)->type);
			}
		}
	}
	return NULL;
}
Matriz * MATRIZ_TRANS(Matriz** matr, Matriz *mat){
	int i,j;
	MATRIZ_FREE(matr);
	if(mat){
		*matr = MATRIZ_CREATE(mat->n,mat->m,mat->type);
		for(i=0;i<(*matr)->m;i++)
		for(j=0;j<(*matr)->n;j++)
		*MATRIZ_EL(*matr,i,j) = *MATRIZ_EL(mat,j,i);
		return *matr;
	}
	return NULL;
}

#endif