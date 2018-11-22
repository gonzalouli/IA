#include "CABECERAS.h"
#include "CABECERAS.h"
#include "Validaposicion.c"

int validaposicion(eEstado	*juego, int op);

int main() {


    int op;

	int validaposicion(juego,op);




	return 0;
}









int validaposicion(eEstado *juego,int op){

	int valido=0;
	

	switch(op){
		case arriba: valido=juego->fila[0]>0;
		break;

		case abajo: valido=juego->fila[0]<N-1;
		break;

		case derecha: valido=juego->columna[0]<N-1;
		break;

		case izquierda: valido=juego->columna[0]>0;
		break;
		}

		return valido

}