#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

int main() {

    vector<vector<int>> grafos ={
        //A, B , C , D
        {0,10,15,20},
        {10,0,35,12},
        {15,35,0,8},
        {20,12,8,0},
    };

    vector<bool> visitado(grafos.size(), false);
    int actual=0;
    int costo=0;

    visitado[actual]=true;
    //empezamos con la primera ciudad
    //por eso hacemos N-1 elecciones

    cout<<"Recorrido: "<<actual;

    for (int paso=0; paso<grafos.size()-1; paso++) {
        int mejorCiudad = -1;
        int mejorDistancia = INT_MAX;
        //esto para que en la comparacion de (distacia<mejorDistancia) entre

        //ahora buscalos la ciudad no visitada más cercana
        for (int i=0; i<grafos.size(); i++) {
            if (!visitado[i] && grafos[actual][i]<mejorDistancia) {
                mejorDistancia = grafos[actual][i];
                mejorCiudad = i;
            }
        }
        //elegimos vorazmente
        visitado[mejorCiudad] = true;
        costo+=mejorDistancia;
        actual=mejorCiudad;
        cout << " -> " << actual;
    }
    cout << endl;
    cout <<"Costo : "<< costo << endl;
    return 0;
}
