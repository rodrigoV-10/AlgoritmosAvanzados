#include <algorithm>
#include <iostream>
#include <vector>
#define N 4

using namespace std;


int calcularImportancia(vector<int>valores,vector<int>v1) {
    int valor=0;
    for (int i=0;i<v1.size();i++) {
        valor+=valores[v1[i]];
    }
    return valor;
}


void backtrackCoscu(int partida,int distAcumulado,int pesoAcumulado,
    int distanciaMax,int pesoMax,int matriz[N][N],vector<int> pesos,
    vector<int> valores,vector<int> &mejorRuta,vector<bool> &visitados,vector<vector<int>>&soluciones) {
    //condicion de para ya recorrí todos los vertices?
    if (mejorRuta.size()>1 && distAcumulado+matriz[partida][0]<=distanciaMax) {
        vector<int>solu = mejorRuta;
        solu.push_back(0);
        soluciones.push_back(solu);
    }
    for (int i=0;i<N;i++) {
        int ruta = matriz[partida][i];
        int w = pesos[i];
        if (ruta+distAcumulado<=distanciaMax
            and w+pesoAcumulado<=pesoMax
            and !visitados[i]) {
            distAcumulado+=ruta;
            pesoAcumulado+=w;
            mejorRuta.push_back(i);
            visitados[i] = true;
            backtrackCoscu(i,distAcumulado,pesoAcumulado,distanciaMax,pesoMax,matriz,pesos,valores,
                mejorRuta,visitados,soluciones);
            distAcumulado-=ruta;
            mejorRuta.pop_back();
            pesoAcumulado-=w;
            visitados[i] = false;
        }
    }
}


int main() {
    int matriz[N][N] ={
        {0,10,15,20},
        {10,0,35,25},
        {35,35,0,30},
        {20,25,30,0}
    };
    int distanciaMax = 60;
    int pesoMax =15;
    vector<int> pesos = {0,5,10,4};
    vector<int> valores = {0,25,40,15};
    vector<bool> visitados(N,false);
    vector<int> mejorRuta;
    vector<vector<int>>soluciones;
    mejorRuta.push_back(0);
    visitados[0] = true;
    backtrackCoscu(0,0,0,
        distanciaMax,pesoMax,matriz, pesos, valores,
        mejorRuta,visitados,soluciones);
    //procedemos a ordenar las rutas
    sort(soluciones.begin(),soluciones.end(),[&valores](vector<int> &v1,vector<int> &v2) {
        int importanciaA = calcularImportancia(valores,v1);
        int importanciaB = calcularImportancia(valores,v2);
        return importanciaA>importanciaB;
    });
    for (int i=0;i<soluciones[0].size();i++) {
        cout<<soluciones[0][i]<<" ";
    }

    return 0;
}
