#include <iostream>
#include <iomanip>

using namespace std;

#define N 6

int main() {

    /*
     * FORMA DE SOLUCION: PROGRAMACION DINAMICA
     *
     * dp[i] representa la maxima ganancia de una seleccion
     * de eventos cuyo ULTIMO evento seleccionado es i.
     *
     * Para cada evento i se buscan todos los eventos j anteriores
     * que sean compatibles.
     */

    int inicio[N] = {1, 4, 6, 6, 5, 8};
    int fin[N]    = {3, 5, 8, 8, 9, 12};
    int pago[N]   = {30, 10, 60, 20, 50, 40};

    int dp[N];
    int padre[N];

    for (int i = 0; i < N; i++) {

        // Caso inicial:
        // seleccionar solamente el evento i
        dp[i] = pago[i];
        padre[i] = -1;

        // Buscamos un evento anterior compatible
        for (int j = 0; j < i; j++) {

            // Debe existir una hora para limpieza
            if (fin[j] + 1 <= inicio[i]) {

                int bono = 0;

                // Exactamente una hora de diferencia
                if (fin[j] + 1 == inicio[i]) {
                    bono = 15;
                }

                int candidato =
                    dp[j] + pago[i] + bono;

                if (candidato > dp[i]) {
                    dp[i] = candidato;
                    padre[i] = j;
                }
            }
        }
    }

    cout << "Arreglo DP:" << endl;

    for (int i = 0; i < N; i++) {
        cout << dp[i] << " ";
    }

    cout << endl << endl;

    // Buscar la mayor ganancia
    int mejor = dp[0];
    int posMejor = 0;

    for (int i = 1; i < N; i++) {
        if (dp[i] > mejor) {
            mejor = dp[i];
            posMejor = i;
        }
    }

    // Reconstruimos los eventos seleccionados
    int seleccion[N];
    int cantidad = 0;

    int pos = posMejor;

    while (pos != -1) {
        seleccion[cantidad] = pos;
        cantidad++;

        pos = padre[pos];
    }

    cout << "Eventos seleccionados: ";

    for (int i = cantidad - 1; i >= 0; i--) {
        cout << "E" << seleccion[i] + 1;

        if (i != 0) {
            cout << " -> ";
        }
    }

    cout << endl;

    cout << "Ganancia maxima: S/. "
         << mejor << endl;

    return 0;
}