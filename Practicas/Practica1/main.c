#include <stdio.h>
#include "puzle.h"


int main(){

tEstado *estado; 

estado= estadoInicial();



unsigned op;
	
	do{	
		dispEstado(estado);
		
		puts("Dame un movimiento para realizar: 1.Arriba 2.Abajo 3.Derecha 4.Izquierda 5.Salir");

		scanf("%d", &op);

		if(op<5){
			
		fflush(stdin);

		dispOperador(op);
		
		if( esValido(op,estado) ){

			puts("Movimiento válido\n");
			estado=aplicaOperador(op,estado);
		
		
		}else puts("Movimiento no valido");


		if( testObjetivo(estado) == 1)
				op=5;
				
				}

}while(op!=5);


puts("Puzle terminado");


return 0;

}
