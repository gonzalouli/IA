#ifndef CABECERAS_H
#define CABECERAS_H

// ==============================================

#include <stdio.h>
#define N 3

typedef struct{

	int celdas[N][N];
	int fila[N*N];
	int columna[N*N];
} eEstado;



eEstado.celdas[N][N]={
	{7,5,3},
	{5,0,1},
	{2,4,6}
};

eEstado *juego;

#define arriba 1
#define abajo 2
#define derecha 3
#define izquierda 4
#define posicion 5


#endif
