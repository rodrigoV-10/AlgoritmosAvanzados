#include <iostream>
#define N 4

using namespace std;

void pintar_tablero (char tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = '.';
        }
    }
}

void imprimir_tablero (char tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }
}

bool validar(int posColunna,int fila,char tablero[N][N]) {
    //verificaremos 3 movimientos
    //por fila
    for (int i=posColunna ; i>=0 ; i--) {
        if (tablero[fila][i]=='Q') {
            return false;
        }
    }
    //por diagonal <- para arriba
    for (int i=fila , j = posColunna; i>=0 && j>=0 ; i-- , j--) {
        if (tablero[i][j]=='Q') {
            return false;
        }
    }

    for (int i=fila , j=posColunna ; i<N && j>=0 ; i++ , j--) {
        if (tablero[i][j]=='Q') {
            return false;
        }
    }

    return true;
}

void n_reinas (int posColunna,char tablero[N][N]) {
    //caso base de la recursividad
    //si llegamos a la última fila es decir que ya colocamos todas las reinas
    if (posColunna==N) {
        cout<<"Se encontró la solución"<<endl;
        imprimir_tablero(tablero);
        return;
    }
    //recorremos por cada fila de la columna donde nos encontramos
    for (int fila = 0; fila < N; fila++) {
        //validamos que la posición donde nos encontremos sea valida
        if (validar(posColunna,fila,tablero)) {
            //si es valido entonces
            tablero[fila][posColunna] = 'Q';
            //asumimos que es correcto e incrementamos la fila
            n_reinas (posColunna+1,tablero);
            //caso contrario hago backtracking
            tablero[fila][posColunna] = '.';
        }
    }
}

int main() {
    char tablero [N][N];
    pintar_tablero (tablero);
    imprimir_tablero (tablero);
    n_reinas (0,tablero);
    return 0;
}
