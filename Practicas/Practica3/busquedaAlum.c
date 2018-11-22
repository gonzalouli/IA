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

int busqueda();

int buscaRepe(tEstado *s, Lista L1);
Lista ordenar(Lista Abiertos,Lista Sucesores);
///Lista InsertarOrden(Lista Abiertos, tElemento *tElemento);
Lista insertar_orden(Lista abiertos, tNodo *n);
Lista a_estrella(Lista abiertos, Lista sucesores);
Lista voraz(Lista abiertos, Lista sucesores);


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


/*int buscaRepe(tEstado *s, Lista L1){

int encontrado=0;

tNodo *extraido = malloc(sizeof(tNodo));

for(int i=0 ;  i<L1->Lmax && encontrado==0 ;  i++){

   extraido = (tNodo*)ExtraerElem(L1,i);

   encontrado = iguales(extraido->estado,s);
}

return encontrado;
}*/





int buscaRepe(tEstado *s, Lista L1) {
    int i = L1->inicio;
    int repetido=0;
    while(i != L1->fin && repetido==0) {
        if(i == L1->Lmax) {
            i = 0;
        }
        tNodo *nnodo = (tNodo*) malloc(sizeof(tNodo));
        nnodo = (tNodo *) ExtraerElem(L1, i);
        if(iguales(nnodo->estado, s)) {
            puts("--Atención-- NODO REPETIDO.");
            repetido=1;
            
        }
        i++;
}
return repetido;
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
         nuevo->valHeuristica = distanciamanhattan(nuevo->estado);
         ///         nuevo->valHeuristica = piezasmalcolocadas(estado); //dependiendo del algoritmo que querramos usar.

         if (!ListaLlena(sucesores)){
            
            InsertarUltimo((void **) nuevo,sucesores);
            dispEstado(nuevo->estado);
         }
      }
  }

   
  return sucesores;
}


Lista insertar_orden(Lista abiertos, tNodo *n) {
    
    int n_insert = 0;
    int i = abiertos->inicio;
    Lista aux = (Lista) CrearLista(MAXI);
    while(i != abiertos->fin) {
        if(i == abiertos->Lmax) {
            i = 0;
        }
        tNodo *nod = (tNodo*) malloc(sizeof(tNodo));
        nod = (tNodo *) ExtraerElem(abiertos, i);
        
        if(nod->valHeuristica > n->valHeuristica && !n_insert) {
            InsertarUltimo((void **) n, aux);
            n_insert = 1;
        }
        InsertarUltimo((void **) nod, aux);
        i++;
    }
    if(!n_insert) {
        InsertarUltimo((void **) n, aux);
    }
    return aux;
}

Lista a_estrella(Lista abiertos, Lista sucesores) {
    
    
    if(ListaVacia(abiertos) && !ListaVacia(sucesores)) {
        InsertarUltimo(ExtraerPrimero(sucesores), abiertos);
        EliminarPrimero(sucesores);
    }
    
    while(!ListaVacia(sucesores)) {
        tNodo *n = (tNodo *) ExtraerPrimero(sucesores);
        abiertos = insertar_orden(abiertos, n);
        EliminarPrimero(sucesores);
    }
    
    return abiertos;
}


Lista voraz(Lista abiertos, Lista sucesores) {
    
    if(ListaVacia(abiertos) && !ListaVacia(sucesores)) {
        InsertarUltimo(ExtraerPrimero(sucesores), abiertos);
        EliminarPrimero(sucesores);
    }
    
    if(!ListaVacia(sucesores)) {
        tNodo *n = (tNodo *) ExtraerPrimero(sucesores);
        EliminarPrimero(sucesores);
        abiertos = insertar_orden(abiertos, n);
    }
    return abiertos;
}






int busqueda()
{  int nestados=0,nnodos=0;
  int busq_voraz;
  puts("Que busqueda desea hacer? 1.Voraz 2.Estrella");
  scanf("%d",&busq_voraz);

   puts("Ha entrado");
   int objetivo=0;
   int repetido;
   tNodo *Actual=(tNodo*)malloc(sizeof(tNodo));

   tNodo *Inicial=nodoInicial();
   tEstado *Final=estadoObjetivo();

   Lista Abiertos= (Lista)CrearLista(MAXI);
   Lista Sucesores;
   Lista Cerrados =(Lista)CrearLista(MAXI);

   InsertarUltimo((void **)Inicial, Abiertos);

   while (!ListaVacia(Abiertos) && objetivo==0 && !ListaLlena(Cerrados))
   {
      Actual = (tNodo*) ExtraerPrimero(Abiertos);
      printf("\n ACTUAL: \n");
      dispEstado(Actual->estado);

      
      objetivo = testObjetivo(Actual->estado);
      EliminarPrimero(Abiertos);
      
      repetido = buscaRepe(Actual->estado, Cerrados);
      if(!ListaLlena(Cerrados)) {
          InsertarUltimo((void **) Actual, Cerrados);
      } else {
         
          puts("ERROR DE MEMORIA");
         
      }
       nestados++;
      if (!objetivo && !repetido)
      {
         nnodos++;
         Sucesores = expandir(Actual);
         /*Abiertos = Concatenar(Abiertos, Sucesores);*/
         if(busq_voraz!=1)
            Abiertos = a_estrella(Abiertos, Sucesores);
         else
            Abiertos = voraz(Abiertos, Sucesores);
}
      printf("\nNumero de elementos en abiertos %d",nnodos);
  
   } 
   dispSolucion(Actual);
   getchar();
   return objetivo;
}

/*
Lista ordenar(Lista Abiertos,Lista Sucesores){

Lista ordenada = (Lista)malloc(MAXI);

for(int i=0;i<Sucesores->Nelem;i++)

  ordenada = InsertarOrden(Abiertos, ExtraerElem(Sucesores,i));

return ordenada;

}



Lista InsertarOrden(Lista Abiertos, tElemento *elementoCerrado){

    tElemento *elementoAbierto;
    Lista *aux;

    for(int j=0;j<Abiertos->Nelem ;j++){

        elementoAbierto = ExtraerElem(Abiertos,j);

        if( piezasmalcolocadas(elementoAbierto) < piezasmalcolocadas(elementoCerrado)){
          
            InsertarUltimo(elementoAbierto, aux);
        }
        else{
            InsertarUltimo(elementoCerrado,aux);

        }

    }
 
}
*/
