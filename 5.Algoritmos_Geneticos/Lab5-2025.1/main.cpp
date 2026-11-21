
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#define ITERACIONES 100
#define NUMIND 20
#define TSELECCION 0.3
#define PCASAMIENTO 0.5
#define TMUTACION 0.3
#define N 7
#define K 2

using namespace std;

// Cada individuo almacena el orden de los clientes
// y el gen donde comienza el segundo repartidor.
struct Individuo {
    vector<int> cromosoma;
    vector<int> cambio_de_repartidor;
};

// Devuelve true si el individuo NO cumple las restricciones.
bool aberracion(const Individuo& ind,
                const int matriz[N][N], int n) {

    int m = n - 1; // Seis clientes; el deposito es el nodo 0

    if ((int)ind.cromosoma.size() != m)
        return true;

    if (ind.cambio_de_repartidor.size() != 1)
        return true;

    // El enunciado cuenta los genes desde 1.
    // Convertimos la posicion a un indice de C++.
    int corte = ind.cambio_de_repartidor[0] - 1;

    // Ambos repartidores deben tener clientes.
    if (corte < 1 || corte >= m)
        return true;

    // PRIMERA RESTRICCION:
    // Cada cliente debe aparecer exactamente una vez.
    vector<bool> visitados(n, false);

    for (int cliente : ind.cromosoma) {

        // El deposito 0 no se incluye en el cromosoma.
        if (cliente <= 0 || cliente >= n)
            return true;

        // No podemos repetir un cliente.
        if (visitados[cliente])
            return true;

        visitados[cliente] = true;
    }

    // Verificamos que no falte ningun cliente.
    for (int cliente = 1; cliente < n; cliente++) {
        if (!visitados[cliente])
            return true;
    }

    // SEGUNDA RESTRICCION:
    // Cada ruta debe existir en el grafo y regresar a A.
    int inicio = 0;

    for (int repartidor = 0; repartidor < K; repartidor++) {

        // El primer repartidor termina antes del corte.
        // El segundo termina al final del cromosoma.
        int fin = (repartidor == 0) ? corte : m;

        int actual = 0; // Deposito A

        for (int i = inicio; i < fin; i++) {

            int siguiente = ind.cromosoma[i];

            // Verificamos que exista la conexion.
            if (matriz[actual][siguiente] == 0)
                return true;

            actual = siguiente;
        }

        // Debe existir una conexion de regreso al deposito.
        if (matriz[actual][0] == 0)
            return true;

        inicio = fin;
    }

    return false;
}

// Calcula la distancia recorrida por los dos repartidores.
// Se invoca para individuos previamente validados.
int calculafitness(const Individuo& ind,
                   const int matriz[N][N], int n) {

    int m = n - 1;
    int corte = ind.cambio_de_repartidor[0] - 1;

    int distanciaTotal = 0;
    int inicio = 0;

    for (int repartidor = 0; repartidor < K; repartidor++) {

        int fin = (repartidor == 0) ? corte : m;
        int actual = 0;

        // Sumamos las distancias desde A hasta el ultimo cliente.
        for (int i = inicio; i < fin; i++) {

            int siguiente = ind.cromosoma[i];

            distanciaTotal += matriz[actual][siguiente];

            actual = siguiente;
        }

        // Sumamos el regreso a A.
        distanciaTotal += matriz[actual][0];

        inicio = fin;
    }

    return distanciaTotal;
}

// Muestra el cromosoma, el corte y su distancia total.
void muestrapoblacion(const vector<Individuo>& poblacion,
                     const int matriz[N][N], int n) {

    for (int i = 0; i < (int)poblacion.size(); i++) {

        cout << "I" << i + 1 << " = (";

        for (int j = 0;
             j < (int)poblacion[i].cromosoma.size(); j++) {

            if (j > 0) cout << ",";

            cout << poblacion[i].cromosoma[j];
        }

        cout << ") cambio_de_repartidor = {"
             << poblacion[i].cambio_de_repartidor[0]
             << "} fo="
             << calculafitness(poblacion[i], matriz, n)
             << endl;
    }
}

// Dos individuos son clones cuando tienen la misma
// secuencia de clientes Y los mismos puntos de corte.
void mataclon(vector<Individuo>& poblacion) {

    map<pair<vector<int>, vector<int>>, bool> vistos;

    vector<Individuo> unicos;

    for (const Individuo& ind : poblacion) {

        auto clave = make_pair(
            ind.cromosoma,
            ind.cambio_de_repartidor
        );

        if (!vistos[clave]) {
            vistos[clave] = true;
            unicos.push_back(ind);
        }
    }

    poblacion = unicos;
}

// Generamos permutaciones de clientes mediante visitados.
// Despues elegimos aleatoriamente el punto de corte.
void generapoblacion(vector<Individuo>& poblacion,
                     const int matriz[N][N], int n) {

    int m = n - 1;
    int intentos = 0;

    // Evita un bucle infinito si el grafo no tiene soluciones.
    const int MAX_INTENTOS = 200000;

    while ((int)poblacion.size() < NUMIND &&
           intentos < MAX_INTENTOS) {

        intentos++;

        Individuo ind;

        vector<bool> visitados(n, false);

        // Generamos un orden de los clientes 1..6.
        for (int i = 0; i < m; i++) {

            int siguiente;

            do {
                siguiente = 1 + rand() % m;
            } while (visitados[siguiente]);

            ind.cromosoma.push_back(siguiente);

            visitados[siguiente] = true;
        }

        // El segundo repartidor puede comenzar
        // en los genes 2, 3, 4, 5 o 6.
        int corte = 2 + rand() % (m - 1);

        ind.cambio_de_repartidor.push_back(corte);

        // Solo guardamos rutas que existan en el grafo.
        if (!aberracion(ind, matriz, n)) {
            poblacion.push_back(ind);
        }
    }

    if ((int)poblacion.size() < NUMIND) {
        cout << "Aviso: solo se generaron "
             << poblacion.size()
             << " individuos validos." << endl;
    }
}

// Calculamos pesos para la ruleta.
// Como minimizamos distancia, los mejores reciben mayor peso.
void calculasupervivencia(
    const vector<Individuo>& poblacion,
    vector<int>& supervivencia,
    const int matriz[N][N], int n) {

    if (poblacion.empty())
        return;

    int mayorDistancia =
        calculafitness(poblacion[0], matriz, n);

    // Buscamos la mayor distancia.
    for (const Individuo& ind : poblacion) {

        int distancia = calculafitness(ind, matriz, n);

        if (distancia > mayorDistancia) {
            mayorDistancia = distancia;
        }
    }

    // Transformamos cada distancia en un peso positivo.
    for (const Individuo& ind : poblacion) {

        int distancia = calculafitness(ind, matriz, n);

        int aptitud = mayorDistancia - distancia + 1;

        supervivencia.push_back(aptitud);
    }
}

// Cada individuo ocupa una cantidad de casillas
// proporcional a su aptitud. La ruleta no tiene
// necesariamente 100 casillas.
void cargaruleta(const vector<int>& supervivencia,
                 vector<int>& ruleta) {

    for (int i = 0; i < (int)supervivencia.size(); i++) {

        for (int j = 0; j < supervivencia[i]; j++) {
            ruleta.push_back(i);
        }
    }
}

// Seleccion natural mediante ruleta.
void seleccion(const vector<Individuo>& poblacion,
               vector<Individuo>& padres,
               const int matriz[N][N], int n) {

    if (poblacion.empty())
        return;

    vector<int> supervivencia;
    vector<int> ruleta;

    calculasupervivencia(
        poblacion, supervivencia, matriz, n
    );

    cargaruleta(supervivencia, ruleta);

    if (ruleta.empty())
        return;

    int npadres = max(
        2,
        (int)round(poblacion.size() * TSELECCION)
    );

    for (int i = 0; i < npadres; i++) {

        int ticket = rand() % ruleta.size();

        padres.push_back(poblacion[ruleta[ticket]]);
    }
}

// Cruzamiento para permutaciones.
// Copiamos una parte del padre y completamos con
// los clientes de la madre que aun no aparezcan.
void creahijo(const Individuo& padre,
              const Individuo& madre,
              Individuo& hijo, int n) {

    int m = n - 1;

    int posi = round(m * PCASAMIENTO);

    vector<bool> usado(n, false);

    // Primera parte: genes del padre.
    for (int i = 0; i < posi; i++) {

        int cliente = padre.cromosoma[i];

        hijo.cromosoma.push_back(cliente);

        usado[cliente] = true;
    }

    // Segunda parte: genes faltantes de la madre.
    for (int cliente : madre.cromosoma) {

        if (!usado[cliente]) {

            hijo.cromosoma.push_back(cliente);

            usado[cliente] = true;
        }
    }

    // Heredamos uno de los puntos de cambio.
    int corte;

    if (rand() % 2 == 0)
        corte = padre.cambio_de_repartidor[0];
    else
        corte = madre.cambio_de_repartidor[0];

    hijo.cambio_de_repartidor.push_back(corte);
}

// Combinamos los padres y aceptamos hijos validos.
void casamiento(vector<Individuo>& poblacion,
               const vector<Individuo>& padres,
               const int matriz[N][N], int n) {

    for (int i = 0; i < (int)padres.size(); i++) {

        for (int j = 0; j < (int)padres.size(); j++) {

            if (i != j) {

                Individuo hijo;

                creahijo(padres[i], padres[j], hijo, n);

                if (!aberracion(hijo, matriz, n)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

// Mutacion: intercambiamos dos clientes.
// Asi evitamos crear clientes repetidos o ausentes.
void mutacion(vector<Individuo>& poblacion,
              const vector<Individuo>& padres,
              const int matriz[N][N], int n) {

    int m = n - 1;

    for (const Individuo& padre : padres) {

        // Aplicamos mutacion con probabilidad del 30%.
        if (rand() % 100 >= TMUTACION * 100)
            continue;

        Individuo mutado = padre;

        int a = rand() % m;
        int b = rand() % m;

        while (a == b) {
            b = rand() % m;
        }

        // Intercambiamos los clientes.
        swap(mutado.cromosoma[a], mutado.cromosoma[b]);

        // Opcionalmente modificamos el punto de corte.
        if (rand() % 2 == 0) {

            mutado.cambio_de_repartidor[0] =
                2 + rand() % (m - 1);
        }

        if (!aberracion(mutado, matriz, n)) {
            poblacion.push_back(mutado);
        }
    }
}

// Inversion: cambiamos el orden de un segmento.
// No significa convertir bits 0 en 1.
void inversion(vector<Individuo>& poblacion,
               const vector<Individuo>& padres,
               const int matriz[N][N], int n) {

    int m = n - 1;

    for (const Individuo& padre : padres) {

        Individuo invertido = padre;

        int a = rand() % m;
        int b = rand() % m;

        if (a > b)
            swap(a, b);

        if (a == b)
            continue;

        reverse(
            invertido.cromosoma.begin() + a,
            invertido.cromosoma.begin() + b + 1
        );

        if (!aberracion(invertido, matriz, n)) {
            poblacion.push_back(invertido);
        }
    }
}

// Eliminamos clones y conservamos los individuos
// con MENOR distancia.
void regenerapoblacion(vector<Individuo>& poblacion,
                      const int matriz[N][N], int n) {

    mataclon(poblacion);

    sort(poblacion.begin(), poblacion.end(),
         [matriz, n](const Individuo& a,
                     const Individuo& b) {

             return calculafitness(a, matriz, n)
                  < calculafitness(b, matriz, n);
         });

    if ((int)poblacion.size() > NUMIND) {

        poblacion.erase(
            poblacion.begin() + NUMIND,
            poblacion.end()
        );
    }
}

// Imprimimos las rutas del mejor individuo.
void muestramejor(const vector<Individuo>& poblacion,
                 const int matriz[N][N], int n) {

    if (poblacion.empty()) {
        cout << "No se encontraron rutas validas." << endl;
        return;
    }

    // Como ordenamos de menor a mayor, el mejor es el primero.
    const Individuo& mejor = poblacion[0];

    int m = n - 1;
    int corte = mejor.cambio_de_repartidor[0] - 1;

    cout << endl << "MEJOR SOLUCION" << endl;

    cout << "Cromosoma: ";
    for (int cliente : mejor.cromosoma)
        cout << cliente << " ";

    cout << endl << "Cambio de repartidor: {"
         << mejor.cambio_de_repartidor[0] << "}" << endl;

    int inicio = 0;

    for (int repartidor = 0; repartidor < K; repartidor++) {

        int fin = (repartidor == 0) ? corte : m;

        int actual = 0;
        int distancia = 0;

        cout << "Repartidor " << repartidor + 1 << ": A";

        for (int i = inicio; i < fin; i++) {

            int siguiente = mejor.cromosoma[i];

            cout << " -> " << siguiente;

            distancia += matriz[actual][siguiente];

            actual = siguiente;
        }

        // Regresamos al deposito.
        distancia += matriz[actual][0];

        cout << " -> A | Distancia: "
             << distancia << endl;

        inicio = fin;
    }

    cout << "Distancia total: "
         << calculafitness(mejor, matriz, n)
         << endl;
}

// Algoritmo genetico principal.
void mochilaAG(const int matriz[N][N], int n) {

    vector<Individuo> poblacion;

    generapoblacion(poblacion, matriz, n);

    if (poblacion.empty()) {
        cout << "No existen individuos para evolucionar."
             << endl;
        return;
    }

    cout << "Poblacion inicial: "
         << poblacion.size() << " individuos" << endl;

    muestrapoblacion(poblacion, matriz, n);

    for (int i = 0; i < ITERACIONES; i++) {

        vector<Individuo> padres;

        seleccion(poblacion, padres, matriz, n);

        casamiento(poblacion, padres, matriz, n);

        mutacion(poblacion, padres, matriz, n);

        // Alternativa opcional a la mutacion:
        // inversion(poblacion, padres, matriz, n);

        regenerapoblacion(poblacion, matriz, n);

        // Mostramos un resumen cada 10 generaciones.
        if (i == 0 || (i + 1) % 10 == 0) {

            cout << "Generacion " << i + 1
                 << " | Individuos distintos: "
                 << poblacion.size()
                 << " | Mejor distancia: "
                 << calculafitness(poblacion[0], matriz, n)
                 << endl;
        }
    }

    muestramejor(poblacion, matriz, n);
}

int main() {

    srand(time(NULL));

    // Grafo dirigido del laboratorio.
    // 0 representa el deposito A.
    // Un 0 fuera de la diagonal indica que no hay arco.
    int matriz[N][N] = {
        // A  1  2  3  4  5  6
        { 0, 4, 0, 3, 0, 0, 0 }, // A
        { 0, 0, 2, 0, 0, 0, 0 }, // 1
        { 8, 0, 0, 0, 2, 0, 0 }, // 2
        { 0, 0, 0, 0, 6, 0, 0 }, // 3
        { 0, 0, 0, 0, 0, 5, 0 }, // 4
        { 0, 0, 0, 0, 0, 0, 2 }, // 5
        { 3, 0, 0, 0, 0, 0, 0 }  // 6
    };

    mochilaAG(matriz, N);

    return 0;
}
