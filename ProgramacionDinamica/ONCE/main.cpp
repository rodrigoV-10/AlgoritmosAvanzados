#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define N 8
#define V 3

void validar(int lima, int extranjero) {

    /*
     * FORMA DE SOLUCION: PROGRAMACION DINAMICA POR TABULACION
     *
     * Se utiliza UNA SOLA matriz dp para las tres validaciones.
     *
     * dp[i][0] = total acumulado
     * dp[i][1] = Extranjero + Oriente acumulado
     * dp[i][2] = diferencia acumulada Grupo A - Grupo B
     *
     * Grupo A:
     * Extranjero, Oriente, Costa Sur, Sierra Centro
     *
     * Grupo B:
     * Costa Norte, Sierra Norte
     */

    int actas[N] = {
        lima,       // 0 Lima
        6000,       // 1 Costa Sur
        12000,      // 2 Costa Norte
        8000,       // 3 Sierra Centro
        12000,      // 4 Sierra Norte
        15000,      // 5 Sierra Sur
        extranjero, // 6 Extranjero
        4500        // 7 Oriente
    };

    /*
     * Para la tercera validacion:
     *
     * +1 -> pertenece al grupo A
     * -1 -> pertenece al grupo B
     *  0 -> no interviene
     */
    int coefDiferencia[N] = {
         0,  // Lima
         1,  // Costa Sur
        -1,  // Costa Norte
         1,  // Sierra Centro
        -1,  // Sierra Norte
         0,  // Sierra Sur
         1,  // Extranjero
         1   // Oriente
    };

    /*
     * Para la segunda validacion:
     * solamente participan Extranjero y Oriente.
     */
    int coefEO[N] = {
        0, // Lima
        0, // Costa Sur
        0, // Costa Norte
        0, // Sierra Centro
        0, // Sierra Norte
        0, // Sierra Sur
        1, // Extranjero
        1  // Oriente
    };

    int dp[N + 1][V];

    // Caso base
    for (int j = 0; j < V; j++) {
        dp[0][j] = 0;
    }

    // Llenado bottom-up
    for (int i = 1; i <= N; i++) {

        // Validacion 1:
        // acumulamos todas las regiones
        dp[i][0] =
            dp[i - 1][0]
            + actas[i - 1];

        // Validacion 2:
        // acumulamos solamente Extranjero + Oriente
        dp[i][1] =
            dp[i - 1][1]
            + coefEO[i - 1] * actas[i - 1];

        // Validacion 3:
        // Grupo A - Grupo B
        dp[i][2] =
            dp[i - 1][2]
            + coefDiferencia[i - 1] * actas[i - 1];
    }

    // Mostrar matriz de soluciones
    cout << endl;
    cout << "MATRIZ DP" << endl;

    cout << setw(5) << "i"
         << setw(12) << "Total"
         << setw(12) << "E+O"
         << setw(15) << "A-B"
         << endl;

    for (int i = 0; i <= N; i++) {

        cout << setw(5) << i
             << setw(12) << dp[i][0]
             << setw(12) << dp[i][1]
             << setw(15) << dp[i][2]
             << endl;
    }

    bool validacion1 =
        dp[N][0] == 95000;

    bool validacion2 =
        dp[N][1] == 7000;

    bool validacion3 =
        abs(dp[N][2]) == 3000;

    cout << endl;

    cout << "Cantidad total de actas: ";

    if (validacion1)
        cout << "correcta";
    else
        cout << "incorrecta";

    cout << endl;

    cout << "Suma Oriente + Extranjero: ";

    if (validacion2)
        cout << "correcta";
    else
        cout << "incorrecta";

    cout << endl;

    cout << "Diferencia entre grupos: ";

    if (validacion3)
        cout << "correcta";
    else
        cout << "incorrecta";

    cout << endl;

    cout << "Resultado final: cantidades ";

    if (validacion1 &&
        validacion2 &&
        validacion3) {

        cout << "correctas";
    }
    else {
        cout << "incorrectas";
    }

    cout << endl;
}

int main() {

    int lima;
    int extranjero;

    cout << "Ingrese actas de Lima: ";
    cin >> lima;

    cout << "Ingrese actas del extranjero: ";
    cin >> extranjero;

    validar(lima, extranjero);

    return 0;
}