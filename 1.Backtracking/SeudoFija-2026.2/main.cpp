#include <iostream>

using namespace std;

#define N 5
#define M 6

/*
    0  -> espacio libre
   -1  -> termita
   -2  -> roca
    1  -> camino recorrido por el robot
*/

void imprimirTablero(int tablero[N][M]) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << tablero[i][j] << "\t";
        }
        cout << endl;
    }
}


// Valida que la posicion:
// 1. Este dentro de la matriz.
// 2. No sea una roca.
// 3. No haya sido visitada.
//
// Tanto 0 como -1 son posiciones validas.
bool esValido(int tablero[N][M], int x, int y) {

    return x >= 0 && x < N &&
           y >= 0 && y < M &&
           tablero[x][y] != -2 &&
           tablero[x][y] != 1;
}


/*
    Forma de solucion: Backtracking.

    El robot prueba los movimientos posibles.
    Si encuentra una termita, aumenta el contador static.

    Si el camino no funciona, restaura la casilla
    y tambien disminuye el contador de termitas
    si habia pasado por una.
*/
bool robotMinero(int x, int y,
                 int tablero[N][M],
                 int movimientos[2][2],
                 int &totalTermitas) {

    static int termitas = 0;


    // Primera llamada
    if (x == 0 && y == 0) {

        termitas = 0;

        tablero[x][y] = 1;
    }


    // CONDICION DE PARADA
    if (x == N - 1 && y == M - 1) {

        totalTermitas = termitas;

        return true;
    }


    // Probamos los movimientos
    for (int i = 0; i < 2; i++) {

        int nx = x + movimientos[i][0];
        int ny = y + movimientos[i][1];


        if (esValido(tablero, nx, ny)) {

            // Guardamos lo que habia originalmente
            int valorAnterior = tablero[nx][ny];


            // Preguntamos si la casilla tenia una termita
            bool habiaTermita = (valorAnterior == -1);


            // ELEGIR
            tablero[nx][ny] = 1;


            if (habiaTermita) {
                termitas++;
            }


            // AVANZAR
            if (robotMinero(nx, ny,
                            tablero,
                            movimientos,
                            totalTermitas)) {

                return true;
            }


            // DESHACER
            tablero[nx][ny] = valorAnterior;


            if (habiaTermita) {
                termitas--;
            }
        }
    }


    return false;
}


int main() {

    int tablero[N][M] = {

        { 0, -1,  0, -2,  0,  0},
        { 0, -2,  0,  0,  0, -2},
        { 0, -1, -1, -2,  0,  0},
        {-2,  0,  0,  0, -1,  0},
        { 0,  0, -2,  0,  0,  0}

    };


    int movimientos[2][2] = {

        {0, 1}, // derecha
        {1, 0}  // abajo

    };


    int totalTermitas = 0;


    cout << "TABLERO INICIAL:" << endl << endl;

    imprimirTablero(tablero);


    cout << endl;


    if (robotMinero(0, 0,
                    tablero,
                    movimientos,
                    totalTermitas)) {

        cout << "Se encontro una ruta." << endl << endl;


        cout << "TABLERO FINAL:" << endl << endl;

        imprimirTablero(tablero);


        cout << endl;

        cout << "Cantidad de termitas encontradas: "
             << totalTermitas << endl;

    }
    else {

        cout << "No existe una ruta de salida." << endl;
    }


    return 0;
}