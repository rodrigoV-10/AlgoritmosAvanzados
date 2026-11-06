#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define N 8
#define TANQUE 12

using namespace std;

struct Camion{
    int capacidad;
    int recargas;
    vector<int>ruta;
};

struct Nodo {
    int punto;
    int distancia;
};

bool compara(Nodo a , Nodo b) {
    return a.distancia > b.distancia;
}

bool cumpleObligatorio(int *obligatorio,vector<bool>visitado) {
    for (int i=0; i<visitado.size(); i++) {
        if (!visitado[i] and obligatorio[i]==1) {
            return false;
        }
    }
    return true;
}

void vorazGrifos(Camion &unCamion,int partida,int destino,int *grifos,
    int distancias[N][N],int *obligatorio) {
    int actual = partida;
    vector<bool>visitado(N,false);
    visitado[actual] = true;
    for (int i=0;i<N;i++) {
        vector<Nodo> vecinos;
        for (int j=0;j<N;j++) {
            int distActual = distancias[actual][j];
            if (!visitado[j] and distActual>0 and distActual<=unCamion.capacidad) {
                //actualizo los datos
                //no puedo llegar al destino sin visitar ciudades
                //obligatorias
                if (j==destino and !cumpleObligatorio(obligatorio,visitado)) {
                    continue;
                }
                Nodo nodo;
                nodo.punto = j;
                nodo.distancia = distActual;
                vecinos.push_back(nodo);
            }
        }
        if (vecinos.empty()) {
            break;
        }
        sort(vecinos.begin(), vecinos.end(), compara);
        Nodo mejor = vecinos[0];
        int siguiente = mejor.punto;
        int distancia = mejor.distancia;


        unCamion.capacidad-=distancia;
        actual = siguiente;
        visitado[actual] = true;
        unCamion.ruta.push_back(actual);

        if (grifos[actual]==1 and unCamion.recargas>0) {
            unCamion.capacidad=TANQUE;
            unCamion.recargas--;
        }

        if (actual==destino) {
            break;
        }

    }
    if (actual == destino and cumpleObligatorio(obligatorio,visitado)) {
        for (int i=0; i<unCamion.ruta.size(); i++) {
            cout << unCamion.ruta[i] << " ";
        }
        cout<<endl<<"Combustible restante: "<<unCamion.capacidad<<endl;
        cout<<"Recargas restantes: "<<unCamion.recargas<<endl;
    }
}


int main() {

    int distancias[N][N] = {
        { 0, 6, 9,11, 0, 0, 0, 0},
        { 6, 0, 3, 0, 5, 0, 0, 0},
        { 9, 3, 0, 0, 0, 4, 0, 0},
        {11, 0, 0, 0, 8, 9, 5, 0},
        { 0, 5, 0, 8, 0, 0, 3, 0},
        { 0, 0, 4, 9, 0, 0, 2, 0},
        { 0, 0, 0, 5, 3, 2, 0,10},
        { 0, 0, 0, 0, 0, 0,10, 0}
    };

    int grifos[N] = {0,0,0,1,0,0,1,0};
    int obligatorio[N] = {0,0,0,0,0,1,0,0};
    //ciudad origen
    int partida = 0;
    int destino = 7;
    Camion unCamion;
    unCamion.capacidad=12;
    unCamion.recargas=2;
    unCamion.ruta.push_back(partida);
    //selecionar la ciudad no visitada más lejada que todavía pueda alcanzarse
    vorazGrifos(unCamion,partida,destino,grifos,distancias,obligatorio);
    return 0;
}
