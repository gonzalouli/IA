/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*#include "puzle.h"*/

// int i = 0, j = 0;

int obtener_i(tEstado *estado) {
    int i = 0, j = 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if(estado->celdas[i][j] == 0) {
                return i;
            }
        }
    }
    return i;
}

int obtener_j(tEstado *estado) {
    int i = 0, j = 0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if(estado->celdas[i][j] == 0) {
                return j;
            }
        }
    }
    return j;
}

tEstado *crearEstado(int celdas[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=celdas[i][j];
         estado->celdas[i][j]=ficha;
         estado->fila[ficha]=i;
         estado->col[ficha]=j;
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACI�N DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
    int i, j;
    for (i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("| %d |", estado->celdas[i][j]);
        }
        puts("");
    }
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Funci�n auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
    int i, j = N;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if(s->celdas[i][j] != t->celdas[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}


int testObjetivo(tEstado *estado)
{

    return iguales(estado, estadoObjetivo());
}


int esValido(unsigned op, tEstado *estado)
{
    int esValido = 0;
    int i = obtener_i(estado);
    int j = obtener_j(estado);
    switch (op) {
        case ARRIBA:
            if(i > 0) {
                puts("Se puede mover arriba.");
                esValido = 1;
            }
            break;
        case ABAJO:
            if(i < N) {
                puts("Se puede mover abajo.");
                esValido = 1;
            }
            break;
        case IZQUIERDA:
            if(j > 0) {
                puts("Se puede mover a la izquierda.");
                esValido = 1;
            }
            break;
        case DERECHA:
            if(j < N) {
                puts("Se puede mover a la derecha.");
                esValido = 1;
            }
            break;
        default:
            puts("Operador Invalido.");
    }
    // if(!esValido) {
    //     puts("No es posible moverlo en esta direcci�n");
    // }
    return esValido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
    tEstado *nuevo = (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));  // Hace una copia del estado

    int i = obtener_i(estado);
    int j = obtener_j(estado);
    /*if(esValido(op, nuevo)) {*/
    switch (op) {
        case ARRIBA:
            nuevo->celdas[i][j] = nuevo->celdas[i-1][j];
            i--;
            nuevo->celdas[i][j] = 0;
            break;
        case ABAJO:
            nuevo->celdas[i][j] = nuevo->celdas[i+1][j];
            i++;
            nuevo->celdas[i][j] = 0;
            break;
        case IZQUIERDA:
            nuevo->celdas[i][j] = nuevo->celdas[i][j-1];
            j--;
            nuevo->celdas[i][j] = 0;
            break;
        case DERECHA:
            nuevo->celdas[i][j] = nuevo->celdas[i][j+1];
            j++;
            nuevo->celdas[i][j] = 0;
            break;
        default:
            puts("por defecto.");
    }
    /*
     *} else {
     *    puts("No es posible moverlo en esta direcci�n");
     *}
     */

    dispEstado(nuevo);

    return nuevo;
}


/*
 *int main(void) {
 *    
 *    [>iguales(estadoInicial(), estadoObjetivo());<]
 *    [>esValido(3, estadoInicial());<]
 *    
 *    tEstado *estado = estadoInicial();
 *    
 *    dispEstado(estado);
 *    puts("");
 *    aplicaOperador(1, estado);
 *    puts("");
 *    aplicaOperador(2, estado);
 *    puts("");
 *    aplicaOperador(3, estado);
 *    puts("");
 *    aplicaOperador(4, estado);
 *
 *    return 0;
 *}
 */
