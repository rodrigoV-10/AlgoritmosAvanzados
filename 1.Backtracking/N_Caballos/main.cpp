#include <iostream>
using namespace std;

#define N 4

void cargarTablero(char tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = '.';
        }
    }
}

void imprimirTablero(char tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }
}

bool esValido(char tablero[N][N],int fila,int columna,int n) {
    int mov[8][2] = {
        mov[0][0]= 2 , mov[0][1]=1,
        mov[1][0]= 1 , mov[1][1]=2,
        mov[2][0]= -1 , mov[2][1]=2,
        mov[3][0]= -2 , mov[3][1]=1,
        mov[4][0]= -2 , mov[4][1]=-1,
        mov[5][0]= -1 , mov[5][1]=-2,
        mov[6][0]= 1 , mov[6][1]=-2,
        mov[7][0]= 2 , mov[7][1]=-1,
    };
    for (int i=0; i < 8; i++) {
        int nx = fila + mov[i][0];
        int ny = columna + mov[i][1];
        if (nx>=0 and nx<N and ny>=0 and ny<N) {
            if (tablero[nx][ny] == 'K') {
                return false;
            }
        }
    }
    return true;
}

void n_caballos(int pos_inicio,int colocados,char tablero[N][N],int &cantidad_soluciones,int n) {
    if (colocados==N) {
        cantidad_soluciones++;
        cout<<"Solucion encontrada!!!"<<endl;
        imprimirTablero(tablero);
        cout<<"===================="<<endl;
        return;
    }

    for (int i=pos_inicio;i<N*N;i++) {
        int fila = i/n;
        int columna = i%n;
        if (esValido(tablero,fila,columna,n)) {
            tablero[fila][columna] = 'K';
            n_caballos(i+1,colocados+1,tablero,cantidad_soluciones,n);
            tablero[fila][columna] = '.';
        }
    }
}


int main() {
    char tablero[N][N];
    cargarTablero(tablero);
    imprimirTablero(tablero);
    int n=4;
    int cantidad_soluciones = 0;
    n_caballos(0,0,tablero,cantidad_soluciones,n);
    return 0;
}
