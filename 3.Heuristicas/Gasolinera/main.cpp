#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <bits/atomic_base.h>

#define MAX 5

using namespace std;

//la estrategia elegida es seleccionar siempre la ciudad no visitada más lejana
//que aún puedo alcanzarse con el combustible disponible

//el tanque posee una capacidad maxima limitada
//intentar llegar a la ciudad destino realizando las menores recargas posibles

void problema_ciudades(int inicio,int destino,int mapa[][MAX],int n,
    int capacidad,vector<bool> grifo) {
    int actual = inicio;
    //grafos no dirigidos
    //arreglo de visitados
    vector<bool>visitados(MAX+1,false);
    vector<int>ruta;
    int recargas=0;
    ruta.push_back(actual);
    int combustible=capacidad;
    visitados[actual] = true;
    while (actual != destino) {
        int mejorCiudad = -1;
        int mayorDistancia = -1;
        //buscamos entre los vecinos de la ciudad actual
        for (int i=0; i<n; i++) {
            if (mapa[actual][i] !=0 && !visitados[i] && mapa[actual][i] <=combustible) {
                if (mapa[actual][i] > mayorDistancia) {
                    mayorDistancia = mapa[actual][i];
                    mejorCiudad = i;
                }
            }
        }
        if (mejorCiudad == -1) {
            cout<<"No existe solucion"<<endl;
            return;
        }
        //actualizamos el combustible
        combustible -= mayorDistancia;
        //nos movemos a la nueva ciudad
        actual = mejorCiudad;
        //marcamos como visitado
        visitados[actual] = true;
        ruta.push_back(actual);

        //si llegamos a una ciudad con grifo y todavía no hemos llegado al destino
        //llenamos tanque
        if (grifo[actual] && actual!=destino) {
            combustible=capacidad;
            recargas++;
        }
    }
    cout<<"Ruta : ";
    for (int i=0; i<ruta.size(); i++) {
        cout<<ruta[i]<<" ";
    }
    cout<<endl;
    cout<<"Recargas: "<<recargas<<endl;
}

int main() {
    int mapa[][MAX]={
        {0,4,7,5,0},
        {4,0,3,2,6},
        {7,3,0,4,7},
        {5,2,4,0,3},
        {0,6,7,3,0}
    };
    int combustible = 10;
    int n = sizeof(mapa)/sizeof(mapa[0]);
    vector<bool>grifo= {true,false,true,false,false};
    problema_ciudades(0,4,mapa,n,combustible,grifo);


    return 0;
}
