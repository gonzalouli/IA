/*******************************************/
/*             BUSQUEDA.C                  */
/*                                         */
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

#include "puzleAlum.c"
#include "listaia.c"

int contador_estados_visit = 0;
int nodos_abiertos = 0;

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


void dispSolucion(tNodo *nodo, Lista l)
{
   dispCamino(nodo);
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
   printf("El numero de estados visitados es => %d.\n", contador_estados_visit);
   printf("El numero de nodos abiertos es => %d.\n", nodos_abiertos);
   printf("El numero de nodos cerrados es => %d.\n", l->Nelem);
}


/* Crea el nodo ra�z. */
tNodo *nodoInicial()
{
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));

   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   inicial->num_veces_visitado = 1;
   return inicial;
}


/* Expande un nodo. */
Lista expandir(tNodo *nodo)
{
   unsigned op;
   Lista sucesores=CrearLista(MAXI);
  // printf("\nLista de Sucesores de Actual: \n");

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
         nuevo->profundidad=nodo->profundidad + 1;

         // Contador de estados.
         contador_estados_visit++;

         if (!ListaLlena(sucesores)){
              InsertarUltimo((void *) nuevo,sucesores);
      //      dispEstado(nuevo->estado);
         }
      }
  }
  //system("pause");
  return sucesores;
}


int busqueda()
{
   int objetivo = 0;
   int repetido = 0;
   tNodo *Actual=(tNodo*) malloc(sizeof(tNodo));

   tNodo *Inicial=nodoInicial();
   //tEstado *Final=estadoObjetivo();

   Lista Abiertos = (Lista) CrearLista(MAXI);
   Lista Cerrados = (Lista) CrearLista(MAXI);
   Lista Sucesores;

   InsertarUltimo((void *) Inicial, Abiertos);

   while (!ListaVacia(Abiertos) && !objetivo)
   {
      Actual = (void *) ExtraerPrimero(Abiertos);
      printf("\n ACTUAL: \n");
      dispEstado(Actual->estado);

      // Esto pa el windows.
      // system("pause");
      // Esto pa el linux, la calidad suprema.
      printf("Press 'Enter' to continue: ... ");
      while ( getchar() != '\n');


      EliminarPrimero(Abiertos);
      objetivo = testObjetivo(Actual->estado);

      repetido = buscaRepe(Actual->estado, Cerrados);
      if(!ListaLlena(Cerrados)) {
          InsertarUltimo((void *) Actual, Cerrados);
      } else {
          puts(ANSI_COLOR_RED);
          puts("ERROR: NO HAY SUFICIENTE MEMORIA.");
          puts(ANSI_COLOR_RESET);
      }

      if (!objetivo && !repetido)
      {
         Sucesores = expandir(Actual);
         Abiertos = Concatenar(Abiertos, Sucesores);
         nodos_abiertos++;
      }
   }
    dispSolucion(Actual, Cerrados);
   return objetivo;
}

int buscaRepe(tEstado *s, Lista l1) {
    int i = l1->inicio;
    while(i != l1->fin) {
        if(i == l1->Lmax) {
            i = 0;
        }
        tNodo *nod = (tNodo*) malloc(sizeof(tNodo));
        nod = (void *) ExtraerElem(l1, i);
        if(iguales(nod->estado, s)) {
            puts(ANSI_COLOR_YELLOW);
            puts("--Atención-- NODO REPETIDO.");
            puts(ANSI_COLOR_RESET);
            return 1;
        }
        i++;
    }
    return 0;
    // for (i = l1->inicio; i < l1->fin; i++) {
    //     tNodo *nod = (tNodo*) malloc(sizeof(tNodo));
    //     nod = (void *) ExtraerElem(l1, i);
    //     if(iguales(nod->estado, s)) {
    //         puts(ANSI_COLOR_YELLOW);
    //         puts("--Atención-- NODO REPETIDO.");
    //         puts(ANSI_COLOR_RESET);
    //         return 1;
    //     }
    // }
    // return 0;
}

int main(void) {

    /*iguales(estadoInicial(), estadoObjetivo());*/
    /*esValido(3, estadoInicial());*/

    int i = obtener_i(estadoInicial());
    int j = obtener_j(estadoInicial());
    printf("i => %d, j => %d.\n", i, j);

    busqueda();
    return 0;
}
