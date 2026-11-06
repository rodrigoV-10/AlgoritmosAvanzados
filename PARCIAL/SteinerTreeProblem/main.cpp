#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define N 8
using namespace std;

struct Nodo {
    int origen;
    int punto;
    int distancia;
};

bool cumpleObligatorio(vector<int>obligatorio,vector<bool>enRed) {
    for (int i=0;i<obligatorio.size();i++) {
        if (obligatorio[i]==1 and !enRed[i]) {
            return false;
        }
    }
    return true;
}
bool compara(Nodo a, Nodo b) {
    if (a.distancia==b.distancia) {
        if (a.punto==b.punto) {
            return a.origen<b.origen;
        }
        return a.punto<b.punto;
    }
    return a.distancia<b.distancia;
}
void recorrerRutaObligatoria(int partida,vector<vector<int>>
    &distancias,vector<int>&obligatorio,vector<pair<int,int>>&ruta) {
    int actual = partida;
    vector<bool>enRed(N,false);
    enRed[actual] = true;
    int costoTotal = 0;
    while (!cumpleObligatorio(obligatorio,enRed)) {
        vector<Nodo>vecinos;
        for (int i=0; i<N ; i++) {
            //sino esta en la red salta a la siguiente ciudad
            if (!enRed[i]) {
                continue;
            }
            //buscar ciudades que no estan conectadas
            for (int j=0; j<N ; j++) {
                int distanciaActual = distancias[i][j];
                if (!enRed[j] and distanciaActual>0) {
                    Nodo nodo;
                    nodo.origen = i;
                    nodo.punto = j;
                    nodo.distancia = distanciaActual;
                    vecinos.push_back(nodo);
                }
            }
        }
        if (vecinos.empty()) {
            return;
        }
        sort(vecinos.begin(),vecinos.end(),compara);
        Nodo mejor = vecinos[0];
        int origen = mejor.origen;
        int siguiente = mejor.punto;
        int distancia = mejor.distancia;
        enRed[siguiente] = true;
        ruta.push_back({origen,siguiente});
        costoTotal+=distancia;
    }
    cout<<"========== RESULTADO =========="<<endl;

    cout<<"Conexiones seleccionadas:"<<endl;

    for (int i=0; i<ruta.size(); i++) {
        int origen = ruta[i].first;
        int destino = ruta[i].second;

        cout<<origen<<" -> "<<destino;
        cout<<" | Costo: "<<distancias[origen][destino];
        cout<<endl;
    }

    cout<<endl;

    cout<<"Ciudades opcionales utilizadas: ";
    for (int i=0; i<N; i++) {
        if (enRed[i] and obligatorio[i]==0) {
            cout<<i<<" ";
        }
    }

    cout<<endl;
    cout<<"Costo total: "<<costoTotal<<endl;
    cout<<"Todas las ciudades obligatorias conectadas: SI";
    cout<<endl;
}

int main() {
    vector<int> obligatorio{1,0,1,0,1,0,0,1};
    vector<vector<int>>distancias={
        {0,2,8,0,0,9,0,0},
        {2,0,2,0,0,3,0,0},
        {8,2,0,3,9,0,0,0},
        {0,0,3,0,2,0,2,0},
        {0,0,9,2,0,0,5,9},
        {9,3,0,0,0,0,2,0},
        {0,0,0,2,5,2,0,2},
        {0,0,0,0,9,0,2,0}
    };
    //debo de conectar todas las ciudades obligatorias
    //tratando de reducir el costo total de la instalacion
    //pueden usarse punto intermedios
    //no es obligatorio usar todas las ciudades del grafo
    int partida = 0;
    vector<pair<int,int>>ruta;
    recorrerRutaObligatoria(partida,distancias,obligatorio,ruta);
    return 0;
}
