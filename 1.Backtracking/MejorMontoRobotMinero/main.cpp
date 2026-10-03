#include <iostream>

using namespace std;

#define N 5
#define M 6

/*
    0    -> espacio libre
    100  -> termita de valor 100
    200  -> termita de valor 200
    -1   -> roca
*/


bool esValido(int tablero[N][M], int x, int y) {

    return x >= 0 && x < N &&
           y >= 0 && y < M &&
           tablero[x][y] != -1;
}


/*
    Forma de solucion: Backtracking.

    Se prueban todos los caminos posibles desde (0,0)
    hasta (N-1,M-1).

    montoActual almacena el dinero del camino que
    estamos recorriendo actualmente.

    mejorMonto almacena el mayor monto encontrado
    entre todos los caminos.
*/
void robotMinero(int x, int y,
                 int tablero[N][M],
                 int movimientos[2][2],
                 int &resultado) {

    static int montoActual = 0;
    static int mejorMonto = 0;


    // Primera llamada
    if (x == 0 && y == 0) {

        montoActual = 0;
        mejorMonto = 0;

        // Por si la posicion inicial tuviera dinero
        if (tablero[x][y] > 0) {
            montoActual += tablero[x][y];
        }
    }


    // CONDICION DE PARADA
    if (x == N - 1 && y == M - 1) {

        if (montoActual > mejorMonto) {
            mejorMonto = montoActual;
        }

        resultado = mejorMonto;

        return;
    }


    // Probar los movimientos
    for (int i = 0; i < 2; i++) {

        int nx = x + movimientos[i][0];
        int ny = y + movimientos[i][1];


        if (esValido(tablero, nx, ny)) {

            // Guardamos el valor de la casilla
            int valor = tablero[nx][ny];


            // ELEGIR
            // Si tiene un monto, lo sumamos
            if (valor > 0) {
                montoActual += valor;
            }


            // AVANZAR
            robotMinero(nx, ny,
                        tablero,
                        movimientos,
                        resultado);


            // DESHACER
            if (valor > 0) {
                montoActual -= valor;
            }
        }
    }


    // Actualizamos el resultado
    resultado = mejorMonto;
}


int main() {

    int tablero[N][M] = {

        {  0, 100,   0,  -1,   0,   0},
        {  0,  -1, 200, 100,   0,  -1},
        {100, 200, 100,  -1, 200,   0},
        { -1,   0, 200, 100, 100,   0},
        {  0,   0,  -1,   0, 200,   0}

    };


    int movimientos[2][2] = {

        {0, 1}, // derecha
        {1, 0}  // abajo

    };


    int mejorMonto = 0;


    robotMinero(0, 0,
                tablero,
                movimientos,
                mejorMonto);


    cout << "Mejor monto encontrado: "
         << mejorMonto << endl;


    return 0;
}