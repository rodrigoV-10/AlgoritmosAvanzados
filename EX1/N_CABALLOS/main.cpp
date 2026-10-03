#include <iostream>

using namespace std;
#define N 8
int mov[8][2];

void inicializarTablero(int tablero[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }
}

void cargarMovimientos() {

    // MOV X         MOV Y
    mov[0][0] = 2; mov[0][1] = 1;
    mov[1][0] = -1; mov[1][1] = 2;
    mov[2][0] = 1; mov[2][1] = 2;
    mov[3][0] = -2; mov[3][1] = 1;
    mov[4][0] = -2; mov[4][1] = -1;
    mov[5][0] = -1; mov[5][1] = -2;
    mov[6][0] = 1; mov[6][1] = -2;
    mov[7][0] = 2; mov[7][1] = -1;
}

void imprimirTablero(int tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout<<tablero[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool esValido(int new_x,int new_y,int tablero[N][N]) {
    //es decir si las posicione son validas y donde me quiero mover es 0
    return new_x>=0 and new_y>=0 and new_x<N and new_y<N and tablero[new_x][new_y]==0;
}

bool solucion(int inicioX,int inicioY,int pos,int tablero[][N]) {
    //si llegamos al fin del tablero
    if (pos == N*N) {
        return true;
    }
    //Donde nos encontramos probamos los 8 movimientos
    for (int i = 0; i < N; i++) {
        //nuevas posiciones
        int new_x = inicioX + mov[i][0];
        int new_y = inicioY + mov[i][1];
        //validamos la nueva posicion
        if (esValido(new_x, new_y, tablero)) {
            tablero[new_x][new_y] = pos;

            //llamada recursiva para el siguiente paso
            if (solucion(new_x,new_y,pos+1,tablero)) {
                return true;
            }
            tablero[new_x][new_y] = 0;

        }
    }


    return false;
}


int main() {
    //std::cout << "Hello, World!" << std::endl;
    int tablero[N][N];
    inicializarTablero(tablero); //todo en 0
    cargarMovimientos();
    int inicioX=0,inicioY=0;
    tablero[inicioX][inicioY] = 1;
    if (solucion(inicioX,inicioY,2,tablero)) {
        cout<<"Solucion encontrada"<<endl;
        imprimirTablero(tablero);
    }else {
        cout<<"No hay solucion"<<endl;
    }

    return 0;
}
