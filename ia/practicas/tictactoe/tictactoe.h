#ifndef TICTAC_H

#define TICTAC_H
#define N 9

typedef struct tNodo {
        int celdas[N];
        int vacias;
} tNodo;

static int tablero_inicial[N] ={0,0,0, 0,0,0, 0,0,0};

// las posiciones serán numeradas de 0 a 8 de la siguiente forma:
//0 1 2
//3 4 5
//6 7 8



tNodo *crearNodo(int celdas[N]);
tNodo *NodoInicial();


/*tNodo *aplicaJugada(tNodo *actual, int jugador, int jugada)
 actual: es el tablero actual,
 jugador: la marca del jugador que tiene el turno
 jugada: indica en qué posición del tablero pondrá la marca
 devuelve: el nuevo Nodo tras aplicar la jugada */
tNodo *aplicaJugada(tNodo *actual, int jugador, int jugada);
int esValida(tNodo *actual, int jugada);

//int terminal(tNodo *actual, int jugador)
// funcion que determina si un nodo es terminal, ha ganado MAX o MIN
// actual: tablero actual
// jugador: 1 si es Max -1 si es Min
//devuelve:  si ha gando MAX 100, si ha ganado MIN -100, empate 0
// si no es terminal tambiŽn devuelve 0

int terminal(tNodo *actual);
tNodo* minimax(tNodo *nodo, int jugador);
int valorMin(tNodo *nodo, int profundidad);
int valorMax(tNodo *nodo, int profundidad);
int min(int i, int j);
int max(int i, int j);
int utilidad(tNodo *nodo);
void dispNodo(tNodo *s);
int opuesto( int jugador);
int lleno(tNodo *s);

tNodo* poda_ab(tNodo *nodo, int jugador);
int valorMin_ab(tNodo *nodo, int jugador, int prof, int alfa, int beta);
int valorMax_ab(tNodo *nodo, int jugador, int prof, int alfa, int beta);


#endif
