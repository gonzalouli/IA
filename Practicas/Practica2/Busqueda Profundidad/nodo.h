/*******************************************/
/* 		    NODO.H                         */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#ifndef _tNodo_
#define _tNodo_
   typedef struct NodoBusqueda{
      tEstado *estado;
      struct NodoBusqueda *padre;
      unsigned operador;
      int costeCamino;
      int profundidad;
      int valHeuristica;
   } tNodoBusqueda;

   typedef tNodoBusqueda tNodo;
#endif





