#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define RESTRICCION 100
#define N 7

using namespace std;

struct Camion {
    int peso;
    int distancia;
    int tiempo;
    vector<int> ruta;
};

struct Nodo {
    int punto;
    int distancia;
};

bool compara(Nodo a, Nodo b) {
    return a.distancia < b.distancia;
}

int rutasPorCamion(int partida,Camion &unCamion,int distancias[][N],
    int *demanda,int *inicio,int *fin,int tiempoServicio,
    vector<bool>&visitado) {
    int actual = partida;
    int cantidad=0;
    for (int i=0; i<N ; i++) {
        vector<Nodo> vecinos;
        for (int j=0; j<N ; j++) {
            int llegada= unCamion.tiempo+distancias[actual][j];
            int inicioAtencion = max(llegada,inicio[j]);
            int distanciaActual = distancias[actual][j];
            if (inicioAtencion<=fin[j] and !visitado[j] and
                distanciaActual > 0
                and demanda[j]+unCamion.peso<=RESTRICCION) {
                Nodo nodo;
                nodo.punto = j;
                nodo.distancia = distancias[actual][j];
                vecinos.push_back(nodo);
            }
        }
        //no encontró más caminos
        if (vecinos.empty()) {
            break;
        }
        sort(vecinos.begin(), vecinos.end(), compara);
        Nodo mejor = vecinos[0];
        int siguiente = mejor.punto;
        int menorDistancia = mejor.distancia;
        unCamion.tiempo = max(unCamion.tiempo+menorDistancia,inicio[siguiente])+tiempoServicio;
        actual=siguiente;
        visitado[actual]=true;
        unCamion.ruta.push_back(actual);
        unCamion.distancia+=menorDistancia;
        unCamion.peso+=demanda[actual];
        cantidad++;
    }
    if (distancias[actual][0]>0) {
        unCamion.ruta.push_back(0);
        unCamion.distancia+=distancias[actual][0];
        unCamion.tiempo+=distancias[actual][0];
    }
    return cantidad;
}

void schedulingRutas(int partida,int distancias[][N],int *demanda,int *inicio,
    int *fin,int tiempoServicio,vector<Camion>&camiones) {
    vector<bool> visitado(N,false);
    int cantidad = 0;
    int contador=0;
    visitado[partida] = true;
    while (cantidad < N-1) {
        Camion unCamion;
        unCamion.peso=0;
        unCamion.distancia=0;
        unCamion.tiempo=0;
        unCamion.ruta.push_back(0);
        contador = rutasPorCamion(partida,unCamion,distancias,demanda,inicio,fin,
            tiempoServicio,visitado);
        camiones.push_back(unCamion);
        if (contador==0) {
            cout<<"No hay solucion"<<endl;
            break;
        }
        cantidad+=contador;
    }
}

int main() {
    //tiempo para descarar los productos es de 10 minutos
    //todos los vehiculos parten a las 8:00
    int distancias[N][N] = {
        { 0, 14, 12,  8, 16, 10, 19},
        {14,  0,  7, 15, 18, 13, 20},
        {12,  7,  0,  9, 14, 12, 17},
        { 8, 15,  9,  0,  6, 15, 22},
        {16, 18, 14,  6,  0,  8, 11},
        {10, 13, 12, 15,  8,  0,  9},
        {19, 20, 17, 22, 11,  9,  0}
    };
    int demanda[N] = {0,30,40,25,50,20,25};

    int inicio[N] = {0,30,20,0,15,0,45};
    int fin[N] =    {0,100,80,50,75,25,120};
    int tiempoServicio = 10;
    vector<Camion> camiones;
    schedulingRutas(0,distancias,demanda,inicio,fin,tiempoServicio,camiones);
    for (int i=0; i<camiones.size(); i++) {
        for (int j=0; j<camiones[i].ruta.size(); j++) {
            cout << camiones[i].ruta[j] << " ";
        }
        cout<<camiones[i].peso<<endl;
        cout << endl;
    }

    return 0;
}
