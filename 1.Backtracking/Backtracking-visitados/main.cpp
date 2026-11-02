#include <iostream>
#include <vector>

using namespace std;

struct Objeto {
    int peso;
    int valor;
};

void mochilaVisitada(int inicio,int pesoActual,int capacidad,
    vector<int>&unaSolucion,vector<vector<int>>&soluciones,
    vector<bool>&visitados,vector<Objeto>&paquetes) {
    if (pesoActual==capacidad) {
        soluciones.push_back(unaSolucion);
        return;
    }
    for (int i=inicio; i<paquetes.size(); i++) {
        int nuevoPeso = pesoActual+paquetes[i].peso;
        if (nuevoPeso && !visitados[i] <= capacidad) {
            visitados[i] = true;
            unaSolucion.push_back(i);
            mochilaVisitada(i+1,nuevoPeso,capacidad,unaSolucion,
                soluciones,visitados,paquetes);
            unaSolucion.pop_back();
            visitados[i] = false;
        }
    }
}


int main() {
    int capacidad =10;
    vector<Objeto> paquetes{
        {2,6},
        {2,10},
        {3,12},
        {5,18},
        {6,22}
    };
    int n = paquetes.size();
    vector<bool> visitados(n, false);
    vector<vector<int>>soluciones;
    vector<int>unaSolucion;
    mochilaVisitada(0,0,capacidad,unaSolucion,soluciones,visitados,paquetes);
    for (int i=0; i<soluciones.size(); i++) {
        for (int j=0; j<soluciones[i].size(); j++) {
            cout << soluciones[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
