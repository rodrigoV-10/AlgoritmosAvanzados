#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define RESTRICCION 100
using namespace std;

struct Camion {
    vector<int> ruta;
    int distancia;
    int peso;
};

struct Nodo {
    int punto;
    int distancia;
};

bool compara(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

void formaLazo(vector<vector<int>>matriz,vector<int>clientes,
    Camion &unCamion,vector<bool>&visitados) {
    int actual = 0;
    visitados[actual]=true;
    for (int i=1; i<matriz.size(); i++) {
        int mejorDistancia = INT_MAX;
        int siguiente = -1;
        for (int j=1; j<matriz.size(); j++) {
            int distanciaActual = matriz[actual][j]; //guardo el valor de esa distancia
            if (!visitados[j] and distanciaActual<mejorDistancia
                and clientes[j-1] + unCamion.peso<=RESTRICCION) {
                siguiente = j;
                mejorDistancia = matriz[actual][j];
            }
            // vector<Nodo> vecinos; Nodo paso;
            // if (matriz[actual][j] and !visitados[j]) {
            //     paso.punto = j;
            //     paso.distancia = matriz[actual][j];
            //     vecinos.push_back(paso);
            // }
            // //he ordenado de acuerdo a la distancia
            // sort(vecinos.begin(), vecinos.end(),compara);
            // //ahora valido si la distancia es m
        }
        if (siguiente == -1) {

            break;
        }
        visitados[siguiente]=true;
        actual=siguiente;
        unCamion.ruta.push_back(siguiente);
        unCamion.peso+=clientes[siguiente-1];
        unCamion.distancia+=mejorDistancia;
    }
    if (matriz[actual][0]!=-1) {
        unCamion.ruta.push_back(0);
        unCamion.distancia+=matriz[actual][0];
    }
}

void camionesTUPIACU(vector<vector<int>>matriz,vector<int>clientes,
    vector<Camion>&camiones) {
    vector<bool> visitados(matriz.size(),false);
    //tenemos 3 camiones y cada camion recorre una ruta
    //envio camion por camion
    for (int i=0; i<camiones.size(); i++) {
        formaLazo(matriz,clientes,camiones[i],visitados);
    }
}


int main() {
    vector<vector<int>> matriz={
        {0,12,15,9,14,10,18},
        {12,0,10,17,20,20,14},
        {15,10,0,11,19,22,22},
        {9,17,11,0,8,21,16},
        {14,20,19,8,0,13,12},
        {10,20,22,21,13,0,16},
        {18,14,22,16,12,16,0},
    };
    vector<int>clientes = {30,40,25,50,20,35};
    //inicializar camiones
    vector<Camion>camiones(3);
    for (int i=0; i<camiones.size(); i++) {
        camiones[i].distancia=0;
        camiones[i].peso=0;
        camiones[i].ruta.push_back(0);
    }
    camionesTUPIACU(matriz,clientes,camiones);
    int distanciaTotal = 0;
    for (int i = 0; i < camiones.size(); i++) {

        cout << "Camion " << i+1 << ": ";

        for (int nodo : camiones[i].ruta) {
            cout << nodo << " ";
        }

        cout << "Peso: " << camiones[i].peso;

        distanciaTotal += camiones[i].distancia;
        cout<<" Distancia "<< camiones[i].distancia<<endl;
    }
    cout << "Distancia total: " << distanciaTotal << endl;
    return 0;
}
