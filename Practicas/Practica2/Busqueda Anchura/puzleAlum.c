/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=puzle[i][j]; 
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

/* VISUALIZACIÓN DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("\nMovimiento ARRIBA:\n"); break;
      case ABAJO:     printf("\nMovimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("\nMovimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("\nMovimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Función auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)
{
 int i = 0, j = 0, iguales = 1;

    for( i = 0 ; i < 2 && iguales == 1 ; i++){
        
        for( j=0 ; j<2 && iguales == 1 ; j++){
            
            if( s->celdas[i][j] != t->celdas[i][j])
                iguales = 0;
        }
    }

    /*if( iguales == 0)
        puts("Los dos puzles tienen las fichas colocadas en ordenes diferentes");
    else
        puts("Los dos puzles tienen las fichas en el mismo orden");
*/
return iguales;
}


int testObjetivo(tEstado *estado)
{
int objetivo=1;

    if( iguales( estado, estadoObjetivo()))

        puts("Se ha alcanzado el estado objetivo");
    else
        objetivo=0;

return objetivo;
}


int esValido(unsigned op, tEstado *estado)
{

int valido;

    switch(op){

        case ARRIBA: valido=estado->fila[0]>0;
                     break;
        case ABAJO:  valido=estado->fila[0]<N-1;
                     break;
        case DERECHA: valido=estado->col[0]<N-1;
                     break;
        case IZQUIERDA: valido=estado->col[0]>0;
                     break;
    }

    return valido;

}



tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
     tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
    memcpy (nuevo, estado,sizeof(tEstado));  // Hace una copia del estado

int cambio;



    switch(op){
    
        case ARRIBA: nuevo->fila[0]-- ;
                     break;
        case ABAJO: nuevo->fila[0]++;
                     break;
        case DERECHA: nuevo->col[0]++;
                     break;
        case IZQUIERDA: nuevo->col[0]--;
                     break;
    }


cambio = estado->celdas[nuevo->fila[0]][nuevo->col[0]];

nuevo->celdas[nuevo->fila[0]][nuevo->col[0]] = 0;

nuevo->celdas[estado->fila[0]][estado->col[0]] = cambio;


return nuevo;

}
