#include <iostream>
#include <vector>

using namespace std;

#define N 3
#define M 6

void cargar_tablero(int tablero[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            tablero[i][j] = 0;
        }
    }
}

void imprimir_tablero(int tablero[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

bool validar_tablero(int tablero[N][M],int  nx,int  ny) {
    return nx>=0 && ny>=0 && nx<N && ny<M and tablero[nx][ny]==0;
}

bool backtrack_palet(int pos,int acumulador,
    int tablero[N][M],int movimientos[8][2]) {
    tablero[pos][M] = pos;

    for (int i = 0; i < 8; i++) {
        int nx = pos + movimientos[i][0];
        int ny = pos + movimientos[i][1];
        if (validar_tablero(tablero, nx, ny)) {
            tablero[nx][ny] = pos+1;
            if (backtrack_palet(pos+1,acumulador+1,tablero,movimientos)) {
                return true;
            }
            tablero[nx][ny] = 0;
            acumulador++;
        }
    }
    return false;
}


int main() {
    int tablero[N][M];
    cargar_tablero(tablero);
    //imprimir_tablero(tablero);
    int movimientos[8][2]={
        {2,2},
        {0,2},
        {-2,2},
        {-2,0},
        {-2,-2},
        {0,-2},
        {2,-2},
        {2,0}
    };
    int acumulador = 0;
    cout<<backtrack_palet(0,acumulador,tablero,movimientos)<<endl;
    return 0;
}
