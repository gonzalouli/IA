#ifndef CASILLAS_H
#define CASILLAS_H

#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
#define NUM_OPERADORES 4
#define Nfil 7
#define Ncol 5

//===================================
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//===================================

#ifndef _tEstado_
#define _tEstado_
   typedef struct {
        int celdas[Nfil][Ncol];
        int fila, columna;
   } tEstado;
#endif


static int caja_inicial[Nfil][Ncol]=
{
  {1, 100, 0, 100, 0},
  {100, 0, 100, 0, 100},
  {0, 200, 0, 100, 0},
  {200, 0, 100, 0, 200},
  {0, 100, 0, 100, 0},
  {300, 0, 300, 0, 300},
  {0, 100, 0, 300, 0}
};


static int caja_final[Nfil][Ncol]=
{
  {0, 100, 0, 100, 0},
  {100, 0, 100, 0, 100},
  {0, 200, 0, 100, 0},
  {200, 0, 100, 0, 200},
  {0, 100, 0, 100, 0},
  {300, 0, 300, 0, 300},
  {0, 100, 0, 300, 1}
};

tEstado *crearEstado(int celdas[Nfil][Ncol]);
tEstado *estadoInicial();
int coste(unsigned op, tEstado *estado);
void dispEstado(tEstado *estado);
void dispOperador(unsigned op);
tEstado *estadoObjetivo();
int esValido(unsigned op, tEstado* estado);
tEstado *aplicaOperador(unsigned op, tEstado *estado);
int iguales(tEstado *s, tEstado *t);
int testObjetivo(tEstado *estado);

#endif // END OF CASILLAS_H
