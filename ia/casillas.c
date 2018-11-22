#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "casillas.h"

int coste_total = 0;

tEstado *crearEstado(int celdas[Nfil][Ncol])
{
    tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
    int i, j, ficha;

    for (i = 0; i < Nfil; i++) {
        for (j = 0; j < Ncol; j++) {
            ficha = celdas[i][j];
            estado->celdas[i][j] = ficha;
           
            if(ficha == 1) {
                estado->fila = i;
                estado->columna = j;
            }
        }
    }
    
    return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(caja_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(caja_final);
}

int coste(unsigned op, tEstado *estado)
{
    int i = estado->fila;
    int j = estado->columna;
    int coste = 0;
    switch (op) {
        case ARRIBA:
            coste += estado->celdas[i - 1][j];
            break;
        case ABAJO:
            coste += estado->celdas[i + 1][j];
            break;
        case IZQUIERDA:
            coste += estado->celdas[i][j - 1];
            break;
        case DERECHA:
            coste += estado->celdas[i][j + 1];
            break;
        default:
            puts("por defecto.");
    }
    coste_total += coste;
    return coste;
}

void dispEstado(tEstado *estado)
{
    int i, j, k;
    for (i = 0; i < Nfil; i++) {
        if(i % 2 == 0) {
            printf(ANSI_COLOR_GREEN);
            printf("|   ");
            printf(ANSI_COLOR_RESET);
            printf("%d   ", estado->celdas[i][0]);
            
            for(j = 1; j < Ncol; j += 2) {
                printf(ANSI_COLOR_GREEN);
                int res = estado->celdas[i][j] / 100;
                
                if(res == 1) { printf("|   "); }
                if(res == 2) { printf("||  "); }
                if(res == 3) { printf("||| "); }
                
                printf(ANSI_COLOR_RESET);
                printf("%d   ", estado->celdas[i][j+1]);
            }
            
            printf(ANSI_COLOR_GREEN);
            printf("|");
            printf(ANSI_COLOR_RESET);
            puts("");
        } else {
            int mayor_k = 0;
            for(j = 0; j < Ncol; j += 2) {
                int res = estado->celdas[i][j] / 100;
                if (res > mayor_k)
                    mayor_k = res;
            }
            
            for (k = 1; k <= mayor_k; k++) {
                for(j = 0; j < Ncol; j += 2) {
                    printf(ANSI_COLOR_GREEN);
                    int res = estado->celdas[i][j] / 100;
                    
                    if(res - k >= 0) { printf("--------"); }
                    else             { printf("        "); }
                }
                puts("");
            }
        }
    }
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA: \n"); break;
      case ABAJO:     printf("Movimiento ABAJO: \n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA: \n"); break;
      case DERECHA:   printf("Movimiento DERECHA: \n"); break;
   }
}

int iguales(tEstado *s, tEstado *t)
{
    int i, j, sonIguales = 1;
    
    for (i = 0; i < Nfil && sonIguales; i++) {
        for (j = 0; j < Ncol && sonIguales; j++) {
            if(s->celdas[i][j] != t->celdas[i][j]) {
                return sonIguales;
            }
        }
    }
    return sonIguales;
}


int testObjetivo(tEstado *estado)
{
    return iguales(estado, estadoObjetivo());
}


int esValido(unsigned op, tEstado *estado)
{
    int esValido = 0;
    int i = estado->fila;
    int j = estado->columna;
    switch (op) {
        case ARRIBA:
            if(i > 0) {
                puts("Se puede mover arriba.");
                esValido = 1;
            }
            break;
        case ABAJO:
            if(i < Nfil - 1) {
                puts("Se puede mover abajo.");
                esValido = 1;
            }
            break;
        case IZQUIERDA:
            if(j > 0) {
                puts("Se puede mover a la izquierda.");
                esValido = 1;
            }
            break;
        case DERECHA:
            if(j < Ncol - 1) {
                puts("Se puede mover a la derecha.");
                esValido = 1;
            }
            break;
        default:
            puts("Operador Invalido.");
    }
    if(!esValido) {
        puts("");
        puts("-----------------------------------");
        puts("No se puede mover en esa direccion.");
        puts("-----------------------------------");
        puts("");
    }
    return esValido;
}

tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
    tEstado *nuevo = (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));  // Hace una copia del estado
    
    printf("El coste en esta operacion es => %d.\n", coste(op, nuevo));
    printf("El coste total es => %d.\n", coste_total);
    
    int aux;
    int i = estado->fila;
    int j = estado->columna;
    switch (op) {
        case ARRIBA:
            nuevo->celdas[i][j] = nuevo->celdas[i-2][j];
            i-=2;
            nuevo->celdas[i][j] = 1;
            break;
        case ABAJO:
            nuevo->celdas[i][j] = nuevo->celdas[i+2][j];
            i+=2;
            nuevo->celdas[i][j] = 1;
            break;
        case IZQUIERDA:
            nuevo->celdas[i][j] = nuevo->celdas[i][j-2];
            j-=2;
            nuevo->celdas[i][j] = 1;
            break;
        case DERECHA:
            nuevo->celdas[i][j] = nuevo->celdas[i][j+2];
            j+=2;
            nuevo->celdas[i][j] = 1;
            break;
        default:
            puts("por defecto.");
    }
    nuevo->fila = i;
    nuevo->columna = j;
    
    dispEstado(nuevo);
    return nuevo;
}

int main(void) {
    
    /*iguales(estadoInicial(), estadoObjetivo());*/
    
    tEstado *estado = estadoInicial();
    dispEstado(estado);
    
    int i, op = 2;
    
    if(esValido(op, estado)) {
        estado = aplicaOperador(op, estado);
    }
    op = 4;
    for(i = 0; i < 3; i++) {
        if(esValido(op, estado)) {
            estado = aplicaOperador(op, estado);
        }
    }
    op = 2;
    for(i = 0; i < 3; i++) {
        if(esValido(op, estado)) {
            estado = aplicaOperador(op, estado);
        }
    }
    
    return 0;
}
