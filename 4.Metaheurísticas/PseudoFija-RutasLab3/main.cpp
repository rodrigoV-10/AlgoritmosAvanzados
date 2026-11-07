#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>

#define ITERACIONES 10000
#define ALFA 0.3
#define N 7
#define CAPACIDAD 100
#define CANT_CAMIONES 3

using namespace std;

struct Camion {
    vector<int> nodos;
    int demandaAcumulada=0;
    int distanciaDelTramo=0;
};

struct Nodo{
    int paso;
    int distancia;
};

bool compara(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

int calcularRCL(double RCL,vector<Nodo>vecinos) {
    int cont=0;
    for(int i=0;i<vecinos.size();i++) {
        if (vecinos[i].distancia<=RCL) {
            cont++;
        }
    }
    return cont;
}

void grasp(int matriz[N][N],vector<int>&demandas,
    vector<Camion>&camiones) {
    srand(time(NULL));
    int mejor = INT_MAX;
    for (int i=0; i<ITERACIONES; i++) {
        vector<Camion> unaSolucion;
        vector<bool> visitados(N, false);
        visitados[0] = true;
        int distanciaTotal=0;
        int clientesAtendidos=0;
        int posActual=0;
        for (int j=0; j<CANT_CAMIONES; j++) {
            Camion unCamion;
            unCamion.nodos.push_back(0);
            while (true) {
                vector<Nodo> vecinos;
                for (int j=1 ; j<N ;j++) {
                    if (!visitados[j] and matriz[posActual][j]!=0 and
                        unCamion.demandaAcumulada+demandas[j]<=CAPACIDAD) {
                        Nodo nodo;
                        nodo.paso = j;
                        nodo.distancia = matriz[posActual][j];
                        vecinos.push_back(nodo);
                    }
                }
                if (vecinos.empty()) break;
                //ordenamos por distancia
                sort(vecinos.begin(), vecinos.end(),compara);
                int beta = vecinos[0].distancia;
                int tao = vecinos[vecinos.size()-1].distancia;
                double RCL = beta+ALFA*(tao-beta);
                int umbral=calcularRCL(RCL,vecinos);
                if (umbral==0) break;
                int indiceAleatorio = rand()%umbral;

                Nodo nodo_aleatorio=vecinos[indiceAleatorio];

                unCamion.nodos.push_back(nodo_aleatorio.paso);
                unCamion.demandaAcumulada+=demandas[nodo_aleatorio.paso];
                unCamion.distanciaDelTramo+=nodo_aleatorio.distancia;
                posActual=nodo_aleatorio.paso;
                visitados[nodo_aleatorio.paso]=true;
                clientesAtendidos++;
            }
            unCamion.nodos.push_back(0);
            unCamion.distanciaDelTramo+=matriz[posActual][0];
            distanciaTotal+=unCamion.distanciaDelTramo;
            unaSolucion.push_back(unCamion);
        }
        if (clientesAtendidos==N-1) {
            if (distanciaTotal<mejor) {
                mejor = distanciaTotal;
                camiones = unaSolucion;
            }
        }
    }

    // Mostrar resultados
    cout << "========== MEJOR SOLUCION ==========" << endl;

    for (int i = 0; i < camiones.size(); i++) {

        cout << "Camion " << i + 1 << endl;

        cout << "Ruta: ";

        for (int j = 0; j < camiones[i].nodos.size(); j++) {

            cout << camiones[i].nodos[j];

            if (j < camiones[i].nodos.size() - 1) {
                cout << " -> ";
            }
        }

        cout << endl;

        cout << "Demanda acumulada: "
             << camiones[i].demandaAcumulada << endl;

        cout << "Distancia recorrida: "
             << camiones[i].distanciaDelTramo << " km" << endl;

        cout << "------------------------------------" << endl;
    }

    cout << "Distancia total de la flota: "
         << mejor << " km" << endl;

}


int main() {
    int matriz[N][N] = {
        { 0, 12, 15,  9, 14, 10, 18},
        {12,  0, 10, 17, 20, 20, 14},
        {15, 10,  0, 11, 19, 22, 22},
        { 9, 17, 11,  0,  8, 21, 16},
        {14, 20, 19,  8,  0, 13, 12},
        {10, 20, 22, 21, 13,  0, 16},
        {18, 14, 22, 16, 12, 16,  0}
    };

    vector<int> demandas = {0, 30, 40, 25, 50, 20, 35};
    vector<Camion> camiones;

    grasp(matriz,demandas,camiones);



    return 0;
}
