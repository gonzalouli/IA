#include <stdio.h>

#include "puzleAlum.c"


int main(){

tEstado *estado; 

*estadoInicial();



   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}





unsigned op;
	
	do{	
		dispEstado(estado);
		
		do{
		puts("Dame un movimiento para realizar: 1.Arriba 2.Abajo 3.Derecha 4.Izquierda 5.Salir");

		scanf("%d", &op);

		}while(op>0 && op<6);

		if(op<5){
		fflush(stdin);

		dispOperador(op);
		
		if( esValido(op,estado)){

			dispOperador(op);

			*estado=*aplicaOperador(op,estado);
		
		}else puts("Movimiento no valido");


		if( testObjetivo(estado) == 1)
				op=5;
				
				}

}while(op!=5);

return 0;

}
