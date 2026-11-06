#include <iostream>
#include <vector>
#include <climits>
#define N 7
#define MAX 100
using namespace std;

struct Camion {
    int peso;
    int distancia;
    vector<int>ruta;
};

void problemaDeRutas(int actual,int distancias[][N],
    Camion &unCamion,int n,int *basura,vector<bool>&visited) {
    for (int i=0; i<N ;i++ ) {
        int siguiente = -1;
        int menorDistancia = INT_MAX;
        for (int j=0; j<N; j++ ) {
            int distancia_actual = distancias[actual][j];
            if (!visited[j] and distancia_actual<menorDistancia
                and basura[j]+unCamion.peso<=MAX) {
                siguiente = j;
                menorDistancia = distancia_actual;
            }
        }
        if (siguiente==-1) {
            break;
        }
        visited[siguiente] = true;
        actual = siguiente;
        unCamion.peso+=basura[siguiente];
        unCamion.distancia+=menorDistancia;
        unCamion.ruta.push_back(actual);
    }
    if (distancias[actual][0]>0 and actual!=0) {
        unCamion.distancia+=distancias[actual][0];
        unCamion.ruta.push_back(0);
    }
}

void generaRuta(int partida,int distancias[][N],vector<Camion>&camiones,int n,
    int* basura) {
    vector<bool> visited(N,false);
    int actual = partida;
    visited[actual] = true;
    int atendidos=0;
    while (atendidos<N-1){
        int contador=0;
        Camion nuevo;
        nuevo.peso=0;
        nuevo.distancia=0;
        nuevo.ruta.push_back(0);
        problemaDeRutas(partida,distancias,nuevo,n,basura,visited);
        camiones.push_back(nuevo);
        atendidos++;
        for (int i=0; i<visited.size(); i++) {
            if (visited[i]==true) {
                contador++;
            }
        }
        if (contador==visited.size()) {
            break;
        }
    }
}

int main() {
    int distancias[N][N] = {
        { 0, 14, 12,  8, 16, 10, 19},
        {14,  0,  7, 15, 18, 13, 20},
        {12,  7,  0,  9, 14, 12, 17},
        { 8, 15,  9,  0,  6, 15, 22},
        {16, 18, 14,  6,  0,  8, 11},
        {10, 13, 12, 15,  8,  0,  9},
        {19, 20, 17, 22, 11,  9,  0}
    };
    int basura[N]= {0,30,40,25,50,20,35};
    int n = 3;
    vector<Camion> camiones;
    generaRuta(0,distancias,camiones, n, basura);
    for (int i=0; i<camiones.size(); i++) {
        cout << "Camion " << i+1 << ": ";

        for (int j=0; j<camiones[i].ruta.size(); j++) {
            cout << camiones[i].ruta[j] << " ";
        }

        cout << "Peso: " << camiones[i].peso;
        cout << " Distancia: " << camiones[i].distancia;
        cout << endl;
    }

    return 0;
}
