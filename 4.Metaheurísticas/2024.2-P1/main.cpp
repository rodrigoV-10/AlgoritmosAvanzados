#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
#include <climits>

#define ITERACIONES 10000
#define ALFA 0.3

using namespace std;

// Ordenamiento descendente (Mejor empezar por los grandes para optimizar espacio)
bool compara(int a, int b) {
    return a > b;
}

// Cuenta cuántos elementos son mayores o iguales al umbral RCL (en orden descendente)
int buscarRCL(const vector<int>& paquetes, double RCL) {
    int contador = 0;
    for (int i = 0; i < paquetes.size(); i++) {
        if (paquetes[i] >= RCL) {
            contador++;
        }
    }
    return contador;
}
//aprovechando al MAXIMO el espacio entre cada una de ellas

void ordenaContenedores(int *paq, int n, int capacidad_maxima) {
    int menor_cantidad_cajas = INT_MAX;
    vector<vector<int>> mejorSolucion;

    srand(time(NULL));

    for (int i = 0; i < ITERACIONES; i++) {
        vector<int> paquetes(paq, paq + n);
        sort(paquetes.begin(), paquetes.end(), compara); // Ordenar de mayor a menor

        // Estructuras para la solución de ESTA iteración
        vector<vector<int>> solucion_actual; // Almacena qué objetos van en cada caja
        vector<int> capacidad_libre_cajas;  // Almacena el espacio disponible de cada caja abierta

        while (!paquetes.empty()) {
            // El mejor (beta) es el más grande, el peor (tao) es el más chico
            int beta = paquetes[0];
            int tao = paquetes[paquetes.size() - 1];

            // Umbral para selección descendente
            double RCL = beta - ALFA * (beta - tao);
            int cantidad_RCL = buscarRCL(paquetes, RCL);

            int indiceAleatorio = rand() % cantidad_RCL;
            int objeto_elegido = paquetes[indiceAleatorio];

            bool asignado = false;
            // Intentar meter el objeto en alguna de las cajas ya abiertas
            for (int c = 0; c < solucion_actual.size(); c++) {
                if (capacidad_libre_cajas[c] >= objeto_elegido) {
                    solucion_actual[c].push_back(objeto_elegido);
                    capacidad_libre_cajas[c] -= objeto_elegido;
                    asignado = true;
                    break; // Ya se acomodó, salimos del bucle de cajas
                }
            }

            // Si no cupo en ninguna caja abierta, abrimos una nueva caja
            if (!asignado) {
                vector<int> nueva_caja;
                nueva_caja.push_back(objeto_elegido);
                solucion_actual.push_back(nueva_caja);
                capacidad_libre_cajas.push_back(capacidad_maxima - objeto_elegido);
            }

            // Eliminar el paquete procesado
            paquetes.erase(paquetes.begin() + indiceAleatorio);
        }

        // Evaluamos si esta asignación total requirió menos cajas que nuestro récord
        if (solucion_actual.size() < menor_cantidad_cajas) {
            menor_cantidad_cajas = solucion_actual.size();
            mejorSolucion = solucion_actual;
        }
    }

    // Impresión de la solución óptima encontrada
    cout << "Menor numero de cajas posibles: " << menor_cantidad_cajas << endl << endl;
    for (int i = 0; i < mejorSolucion.size(); i++) {
        cout << "Contenedor " << i + 1 << ": [ ";
        for (int j = 0; j < mejorSolucion[i].size(); j++) {
            cout << mejorSolucion[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

int main() {
    int paq[] = {4, 8, 1, 4, 2, 1};
    int n = sizeof(paq) / sizeof(paq[0]);
    int peso = 10;

    ordenaContenedores(paq, n, peso);
    return 0;
}