#include <iostream>
#include <iomanip>

using namespace std;

// Cambia este valor a 5 para pruebas rápidas. 8 es el tablero de ajedrez real.
#define N 8

// Los 8 posibles movimientos de un caballo en forma de "L"


int mov[8][2];


// Inicializa el tablero con 0 (casillas vacías)
void inicializarTablero(int tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }
}

void cargarMovimientos() {
    mov[0][0] = 2; mov[0][1] = 1;
    mov[1][0] = 1; mov[1][1] = 2;
    mov[2][0] = -1; mov[2][1] = 2;
    mov[3][0] = -2; mov[3][1] = 1;
    mov[4][0] = -2; mov[4][1] = -1;
    mov[5][0] = -1; mov[5][1] =-2;
    mov[6][0] = 1; mov[6][1] = -2;
    mov[7][0] = 2; mov[7][1] = -1;
}

// Imprime el tablero con un formato ordenado
void imprimirTablero(int tablero[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(3) << tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------" << endl;
}

// Verifica si la siguiente posición es válida (dentro del tablero y no visitada)
bool esValido(int nx, int ny, int tablero[N][N]) {
    return (nx >= 0 && nx < N && ny >= 0 && ny < N && tablero[nx][ny] == 0);
}

// Función recursiva con Backtracking
bool resolverCaballo(int x, int y, int paso, int tablero[N][N]) {
    // Caso base: Si el paso a dar es mayor al número total de casillas, terminamos
    if (paso > N * N) {
        return true;
    }

    // Probamos los 8 movimientos posibles desde la posición actual (x, y)
    for (int i = 0; i < 8; i++) {
        int nx = x + mov[i][0];
        int ny = y + mov[i][1];

        if (esValido(nx, ny, tablero)) {
            // MARCAMOS la casilla con el número de paso actual
            tablero[nx][ny] = paso;

            // Llamada recursiva para el siguiente paso
            if (resolverCaballo(nx, ny, paso + 1, tablero)) {
                return true; // Se encontró una ruta completa
            }

            // BACKTRACKING: El camino falló, desmarcamos la casilla (la volvemos a poner en 0)
            tablero[nx][ny] = 0;
        }
    }

    // Si ninguno de los 8 movimientos funciona, retornamos false para retroceder
    return false;
}

int main() {
    int tablero[N][N]{};
    inicializarTablero(tablero);
    cargarMovimientos();

    // Definimos la posición inicial del caballo
    int inicioX = 0;
    int inicioY = 0;

    // Marcamos el primer paso en la posición inicial
    tablero[inicioX][inicioY] = 1;

    cout << "Buscando solucion para un tablero de " << N << "x" << N << "..." << endl;

    // Empezamos la búsqueda intentando colocar el paso 2
    if (resolverCaballo(inicioX, inicioY, 2, tablero)) {
        cout << "Solucion encontrada:" << endl;
        imprimirTablero(tablero);
    } else {
        cout << "No existe solucion desde esta posicion." << endl;
    }

    return 0;
}