#include <stdio.h>

#include "puzleAlum.c"


int main(){

tEstado *estado; 

unsigned op;
	
	do{
		dispEstado(estado);
		
		puts("Dame un movimiento para realizar: 1.Arriba 2.Abajo 3.Derecha 4.Izquierda 0.Salir");

		scanf("%d", &op);
		
		fflush(stdin);

		dispOperador(op);
		
		if( esValido(op,estado)){

			dispOperador(op);

			*aplicaOperador(op,estado);
		
		}else puts("Movimiento no valido");

		testObjetivo(estado);

		if( testObjetivo(estado) == 1)
				op=0;
				
}while(op!=0);

return 0;

}
