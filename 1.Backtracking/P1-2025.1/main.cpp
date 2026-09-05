#include <iostream>
#include <iomanip>
using namespace std;

#define N 8

void cargar_tablero(int tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }
}

void imprimir_tablero(int tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout <<setw(3)<< tablero[i][j] << " ";
        }
        cout << endl;
    }
}

bool validarMov(int nx,int ny,int tablero[N][N]) {
    return nx>=0 && nx<N && ny>=0 && ny<N and tablero[nx][ny] == 0;
}


bool caminoDelRey(int pos,int x,int y,int tablero[N][N],
    int movimientos[8][2]) {
    tablero[x][y] = pos;
    if (pos==N*N) {
        imprimir_tablero(tablero);
        return true;
    }
    for (int i = 0; i < 8; i++) {
        int nx = x + movimientos[i][0];
        int ny = y + movimientos[i][1];
        if (validarMov(nx,ny,tablero)) {
            //hacer cambio
            tablero[nx][ny] = pos+1;
            if (caminoDelRey(pos+1,nx,ny,tablero,movimientos)) {
                return true;
            }
            //backtrack
            tablero[nx][ny] =0;
            //deshacercambio
        }
    }
    return false;
}

int main() {
    int tablero[N][N];
    int movimientos[8][2]={
        {-1,-1},
        {0,1},
        {1,0},
        {1,1},
        {1,-1},
        {0,-1},
        {-1,0},
        {-1,+1}
    };
    cargar_tablero(tablero);
    //imprimir_tablero(tablero);
    cout<<caminoDelRey(1,3,3,tablero,movimientos);
    return 0;
}
