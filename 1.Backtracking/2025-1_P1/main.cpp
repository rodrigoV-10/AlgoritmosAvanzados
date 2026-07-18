#include <iostream>

using namespace std;

#define N 8
int mov[8][2];

bool validar(int posX,int posY,int tablero[N][N]) {
    return posX>=0 && posX<N && posY>=0 && posY<N and tablero[posX][posY]==0;
}

void imprimirTablero(int tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

void cargaMovimientos() {
    //   x            y
    mov[0][0] = 0  ; mov[0][1]= 1;
    mov[1][0] = 0  ; mov[1][1]=-1;
    mov[2][0] = -1 ; mov[2][1]= 0;
    mov[3][0] = 1  ; mov[3][1]= 0;
    mov[4][0] = -1 ; mov[4][1]= 1;
    mov[5][0] =  1 ; mov[5][1]= -1;
    mov[6][0] = -1 ; mov[6][1]= -1;
    mov[7][0] =  1 ; mov[7][1]= 1;
    /* el orden importa
    * mov[0][0]= -1;mov[0][1]= -1;
      mov[1][0]= -1;mov[1][1]=  0;
      mov[2][0]= -1;mov[2][1]=  1;
      mov[3][0]=  0;mov[3][1]=  1;
      mov[4][0]=  1;mov[4][1]=  1;
      mov[5][0]=  1;mov[5][1]=  0;
      mov[6][0]=  1;mov[6][1]= -1;
      mov[7][0]=  0;mov[7][1]= -1;
     *
     *
     */
}

int caminoDelRey(int posX,int  posY,int paso,int tablero[N][N]) {
    if (paso==64) {
        imprimirTablero(tablero);
        return 1;
    }
    //pr los 8 movimientos
    for (int i=0 ; i<N ; i++) {
        int nx = posX + mov[i][0];
        int ny = posY + mov[i][1];
        if (validar(nx,ny,tablero)) {
            tablero[nx][ny] = paso+1;
            if (caminoDelRey(nx,ny,paso+1,tablero)) {
                return 1;
            }else {
                tablero[nx][ny] = 0;
            }
        }
    }
    return 0;
}

int main() {

    int tablero[N][N]{};
    //int solucion[N][N]{};
    int posX=3, posY=3;
    imprimirTablero(tablero);
    //8 posibles movimientos
    cargaMovimientos();
    tablero[posX][posY] = 1;
    caminoDelRey(posX, posY,1 ,tablero);




    return 0;
}
