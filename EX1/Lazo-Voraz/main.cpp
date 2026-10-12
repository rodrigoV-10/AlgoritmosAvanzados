#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>

using namespace std;

bool cicloHamiltoniano(vector<vector<int>>grafo,int inicio,
    vector<int>&ruta,int &costoTotal) {
    int n= grafo.size();
    int actual = inicio;
    ruta.push_back(actual);
    costoTotal=0;
    vector<bool> visited(n,false);
    visited[actual]=true;
    for (int i=1; i<n; i++) {
        int menorPeso = INT_MAX;
        int siguiente=-1;
        for (int j=0; j<n; j++) {
            if (!visited[j] and grafo[actual][j]<menorPeso) {
                menorPeso = grafo[actual][j];
                siguiente=j;
            }
        }
        if (siguiente==-1) {
            return false;
        }
        visited[siguiente]=true;
        ruta.push_back(siguiente);
        costoTotal+=menorPeso;
        actual=siguiente;
    }
    if (grafo[actual][inicio]!=-1) {
        ruta.push_back(inicio);
        costoTotal+=grafo[actual][inicio];
        return true;
    }
    return false;
}


int main() {
    vector<vector<int>> grafo = {
        {0,   10, 15, 20},
        {10,  0,  35, 25},
        {15,  35, 0,  30},
        {20,  25, 30, 0}
    };
    int inicio = 0;
    vector<int> ruta;
    int costoTotal=0;
    if (cicloHamiltoniano(grafo,inicio,ruta,costoTotal)) {
        for (int i=0 ; i<ruta.size(); i++) {
            cout<<ruta[i]<<" ";
        }
        cout<<costoTotal<<endl;
    }
    return 0;
}
