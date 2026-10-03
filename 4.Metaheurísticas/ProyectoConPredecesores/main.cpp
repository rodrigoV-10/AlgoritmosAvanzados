#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>

#define ITERACIONES 10000
#define ALFA 0.4

using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int> predecesores;
};

// 1. EXTRAEMOS LA FÓRMULA: Es vital usarla para calcular el límite RCL (Beta y Tau)
// Multiplicamos por 1.0 para no perder los decimales en la división
double calcularHeuristica(Proyecto p) {
    return (1.0 * p.beneficio * p.ganancia) / p.costo;
}

// Comparamos usando la función extraída
bool compara(Proyecto a, Proyecto b) {
    return calcularHeuristica(a) > calcularHeuristica(b);
}

// Tu función original, ¡funciona excelente!
bool verifica(Proyecto proy, vector<int> solu) {
    int cont = 0;
    if (proy.predecesores.size() == 0) return true;

    for (int i = 0; i < proy.predecesores.size(); i++) {
        for (int j = 0; j < solu.size(); j++) {
            if (proy.predecesores[i] == solu[j]) {
                cont++;
            }
        }
    }
    if (cont == proy.predecesores.size())
        return true;
    return false;
}

// Función auxiliar para saber si ya hicimos el proyecto y no repetirlo
bool yaSeleccionado(int id, vector<int> solu) {
    for (int i = 0; i < solu.size(); i++) {
        if (solu[i] == id) return true;
    }
    return false;
}

// Tu contador de RCL optimizado con el break
int buscarRCL(double RCL, vector<Proyecto> &candidatos) {
    int cont = 0;
    for (int i = 0; i < candidatos.size(); i++) {
        if (calcularHeuristica(candidatos[i]) >= RCL) {
            cont++;
        } else {
            break;
        }
    }
    return cont;
}

void seleccionaProyectosGRASP(vector<Proyecto>& proy_base, int presu_max) {
    int mejor_ganancia = INT_MIN;
    vector<int> mejor_solucion;

    srand(time(NULL));

    for (int i = 0; i < ITERACIONES; i++) {
        int presu_actual = presu_max;
        int ganancia_actual = 0;
        vector<int> solucion;
        vector<Proyecto> candidatos;

        // Buscamos los candidatos INICIALES
        for (int j = 0; j < proy_base.size(); j++) {
            if (proy_base[j].costo <= presu_actual && verifica(proy_base[j], solucion)) {
                candidatos.push_back(proy_base[j]);
            }
        }

        while (!candidatos.empty()) {

            // Ordenamos de mayor a menor según TU fórmula de beneficio/costo
            sort(candidatos.begin(), candidatos.end(), compara);

            // Obtenemos el valor heurístico del mejor y del peor
            double beta = calcularHeuristica(candidatos[0]);
            double tau = calcularHeuristica(candidatos[candidatos.size() - 1]);

            double limite_rcl = beta - ALFA * (beta - tau);

            int rangoRCL = buscarRCL(limite_rcl, candidatos);
            int indiceAleatorio = rand() % rangoRCL;

            // Elegimos un proyecto de la RCL
            Proyecto proyecto_elegido = candidatos[indiceAleatorio];

            // ACTUALIZAMOS
            ganancia_actual += proyecto_elegido.ganancia;
            presu_actual -= proyecto_elegido.costo;
            solucion.push_back(proyecto_elegido.id);

            // BORRAMOS y calculamos nuevos candidatos
            candidatos.clear();
            for (int j = 0; j < proy_base.size(); j++) {
                // Verificamos que no esté en la solución, que alcance el dinero y se cumplan predecesores
                if (!yaSeleccionado(proy_base[j].id, solucion) &&
                    proy_base[j].costo <= presu_actual &&
                    verifica(proy_base[j], solucion)) {

                    candidatos.push_back(proy_base[j]);
                }
            }
        }

        // Evaluamos si es la mejor ejecución de las 10,000
        if (ganancia_actual > mejor_ganancia) {
            mejor_ganancia = ganancia_actual;
            mejor_solucion = solucion;
        }
    }

    // Resultados
    cout << "=== MEJOR SOLUCION GRASP ===" << endl;
    cout << "Ganancia: " << mejor_ganancia << endl;
    cout << "Proyectos elegidos: ";
    for (int i = 0; i < mejor_solucion.size(); i++) {
        cout << mejor_solucion[i] << " ";
    }
    cout << endl;
}

int main() {
    // Declaramos como vector en lugar de arreglo clásico para facilitar su manejo en la función
    vector<Proyecto> cartera = {
        {1, 80, 150, 2, {}},
        {2, 20, 80, 5, {4}},
        {3, 100, 300, 1, {1, 2}},
        {4, 100, 150, 4, {}},
        {5, 50, 80, 2, {}},
        {6, 10, 50, 1, {2}},
        {7, 50, 120, 2, {6}},
        {8, 50, 150, 4, {6}},
    };

    int presu = 250;

    seleccionaProyectosGRASP(cartera, presu);

    return 0;
}