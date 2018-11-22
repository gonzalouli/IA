/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzle.h"
#include "nodo.h"
#include "listaia.h"
#include "busquedaAlum.h"


void dispCamino(tNodo *nodo)
{
   if (nodo->padre==NULL)
   {
      printf("\n\nInicio:\n");
      dispEstado(nodo->estado);
   }
   else
   {
      dispCamino(nodo->padre);
      dispOperador(nodo->operador);
      dispEstado(nodo->estado);
      printf("\n");
   }
}


void dispSolucion(tNodo *nodo)
{
   dispCamino(nodo);
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
}


/* Crea el nodo raíz. */
tNodo *nodoInicial()
{
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));

   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   return inicial;
}








/* Expande un nodo. */
Lista expandir(tNodo *nodo)
{  
   unsigned op;
   Lista sucesores=CrearLista(MAXI);
  printf("\nLista de Sucesores de Actual: \n");
   for (op=1;op<=NUM_OPERADORES;op++)
   {
      if (esValido(op,nodo->estado))
      {
         tNodo *nuevo=(tNodo *) malloc(sizeof(tNodo));
         tEstado *s=(tEstado *) malloc(sizeof(tEstado));
         s=aplicaOperador(op,nodo->estado);
         nuevo=(tNodo *) malloc(sizeof(tNodo));
         nuevo->estado=s;
         nuevo->padre=nodo;
         nuevo->operador=op;
         nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
         nuevo->profundidad=nodo->profundidad+1;
         
         if (!ListaLlena(sucesores)){
            InsertarUltimo((void *) nuevo,sucesores);
            dispEstado(nuevo->estado);
         }
      }
  }

   
  return sucesores;
}




int busqueda()
{  int nestados=0,nnodos=0,nnodos1=0;

   puts("Ha entrado");
   int objetivo=0;
   tNodo *Actual=(tNodo*) malloc(sizeof(tNodo));

   tNodo *Inicial=nodoInicial();
   tEstado *Final=estadoObjetivo();

   Lista Abiertos= (Lista)CrearLista(MAXI);
   Lista Sucesores;
   Lista Cerrados =(Lista)CrearLista(MAXI);

   InsertarUltimo((void *)Inicial, Abiertos);

   while (!ListaVacia(Abiertos) && !objetivo)
   {
      Actual= (void *) ExtraerPrimero(Abiertos);

   printf("\n ACTUAL: \n");

    dispEstado(Actual->estado);
      
      EliminarPrimero(Abiertos);
      objetivo=testObjetivo(Actual->estado);
      
	  if (!objetivo)
      {///estrategia de anchura
         Sucesores = expandir(Actual); 
		   nestados++;
         printf("%d Estado visitado",nestados);
         Abiertos=Concatenar(Sucesores,Abiertos); ///sucesores,abiertos para profundidad
		   
            }
      }
   }   
    dispSolucion(Actual);
   getchar();
   return objetivo;
}
