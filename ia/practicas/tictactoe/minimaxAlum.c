#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tictactoe.h"

#define LIMITE 300

int min(int i, int j) {
    if(j < i) {
        i = j;
    }
    return i;
}

int max(int i, int j) {
    if(j > i) {
        i = j;
    }
    return i;
}

int heuristica(tNodo *nodo) {
    unsigned opciones[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i=0,res=0, contador_maquina = 0, contador_humano = 0;
    
    while (res == 0 && i < 8) {
        if(nodo->celdas[opciones[i][0]] == 1 &&
           nodo->celdas[opciones[i][1]] == 1 &&
           nodo->celdas[opciones[i][2]] == 1) {
            contador_humano++;
        }
        if(nodo->celdas[opciones[i][0]] == -1 &&
           nodo->celdas[opciones[i][1]] == -1 &&
           nodo->celdas[opciones[i][2]] == -1) {
            contador_maquina++;
        }
        i++;
    }
    return (contador_maquina - contador_humano);
}

int valorMin(tNodo *nodo, int profundidad) {
    int valor_min, jugada, jugador = -1;
    if(profundidad < LIMITE) {
        if(nodo->vacias == 0 || terminal(nodo)) {
            valor_min = heuristica(nodo);
        } else {
            valor_min = 100000;
            for (jugada = 0; jugada < N; jugada++) {
                if(esValida(nodo, jugada)) {
                    valor_min = min(valor_min, valorMax(aplicaJugada(nodo, jugador, jugada), ++profundidad));
                }
            }
        }
    }
    return valor_min;
}

int valorMax(tNodo *nodo, int profundidad) {
    int valor_max, jugada, jugador = 1;
    if(profundidad < LIMITE) {
        if(nodo->vacias == 0 || terminal(nodo)) {
            valor_max = heuristica(nodo);
        } else {
            valor_max = -100000;
            for (jugada = 0; jugada < N; jugada++) {
                if(esValida(nodo, jugada)) {
                    valor_max = max(valor_max, valorMin(aplicaJugada(nodo, jugador, jugada), ++profundidad));
                }
            }
        }
    }
    return valor_max;
}

tNodo* minimax(tNodo *nodo, int jugador) {
    int max, max_actual, jugada, mejorJugada, i, profundidad = 0;
    tNodo *intento = malloc(sizeof(tNodo));
    
    max = -10000;
    for (jugada = 0; jugada < N; jugada++) {
        if(esValida(nodo, jugada)) {
            intento = aplicaJugada(nodo, jugador, jugada);
            max_actual = valorMin(intento, profundidad);
            if(max_actual > max) {
                max = max_actual;
                mejorJugada = jugada;
            }
        }
    }
    printf("mejor jugada => %d.\n", mejorJugada);
    nodo = aplicaJugada(nodo, jugador, mejorJugada);
    return nodo;
}

tNodo *jugadaAdversario(tNodo *t) {
     int jugada = 0;
     printf("\nJugada ([0..8])?: ");
     scanf("%d", &jugada);
     while (!esValida(t,jugada))
     {
        printf("\n Intenta otra posicion del tablero \n");
        printf("\n");
        printf("\nJugada ([0..8])?: ");
        scanf("%d", &jugada);
     }
     t=aplicaJugada(t,-1,jugada);
     return t;
}

tNodo* poda_ab(tNodo *nodo, int jugador) {
    int alfa, beta, jugada, mejorJugada, prof, v;
    tNodo *intento = malloc(sizeof(tNodo));
    
    alfa = -10000;
    beta = +10000;
    prof = 1;
    jugada = 0;
    
    while(jugada < N) {
        if(esValida(nodo, jugada)) {
            intento = aplicaJugada(nodo, jugador, jugada);
            v = valorMin_ab(intento, opuesto(jugador), (prof+1), alfa, beta);
            if(v > alfa) {
                alfa = v;
                mejorJugada = jugada;
            }
        }
        jugada++;
    }
    if(esValida(nodo, mejorJugada)) {
        nodo = aplicaJugada(nodo, jugador, mejorJugada);
    }
    return nodo;
}

int valorMax_ab(tNodo *nodo, int jugador, int prof, int alfa, int beta) {
    int vmax, jugada;
    tNodo *intento = malloc(sizeof(tNodo));
    
    if(nodo->vacias == 0 || terminal(nodo)) {
        vmax = heuristica(nodo);
    } else if (prof == LIMITE) {
        vmax = heuristica(nodo);
    } else {
        jugada = 0;
        while(jugada < N && alfa < beta) {
            if(esValida(nodo, jugada)) {
                intento = aplicaJugada(nodo, jugador, jugada);
                alfa = max(alfa, valorMin_ab(intento, opuesto(jugador), (prof+1), alfa, beta));
            }
            jugada++;
        }
        vmax = alfa;
    }
    return vmax;
}

int valorMin_ab(tNodo * nodo, int jugador, int prof, int alfa, int beta) {
    int vmin, jugada;
    tNodo *intento = malloc(sizeof(tNodo));
    
    if(nodo->vacias == 0 || terminal(nodo)) {
        vmin = heuristica(nodo);
    } else if (prof == LIMITE) {
        vmin = heuristica(nodo);
    } else {
        jugada = 0;
        while(jugada < N && alfa < beta) {
            if(esValida(nodo, jugada)) {
                intento = aplicaJugada(nodo, jugador, jugada);
                beta = min(beta, valorMax_ab(intento, opuesto(jugador), (prof+1), alfa, beta));
            }
            jugada++;
        }
        vmin = beta;
    }
    return vmin;
}
