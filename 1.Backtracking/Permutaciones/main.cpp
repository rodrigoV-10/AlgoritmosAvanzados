#include <iostream>
#include <vector>

using namespace std;

void generaPermutacion(vector<int>&numeros,vector<int> &actual,
    vector<bool>&visitado,vector<vector<int>> &soluciones) {
    //si la permutacion tiene el mismo tamaño que el arreglo original
    if (actual.size()==numeros.size()) {
        soluciones.push_back(actual);
        return;
    }
    for (int i=0;i<numeros.size();i++) {
        if (visitado[i])continue;
        //
        visitado[i] = true;
        actual.push_back(numeros[i]);
        generaPermutacion(numeros, actual, visitado, soluciones);
        actual.pop_back();
        visitado[i] = false;
    }
}

int main() {
    vector<int> numeros= {1,2,3};
    vector<int> actual;
    vector<bool>visitado(numeros.size(), false);
    vector<vector<int>>soluciones;
    generaPermutacion(numeros, actual,visitado, soluciones);
    for (int i=0;i<soluciones.size();i++) {
        for (int j=0;j<soluciones[i].size();j++) {
            cout<<soluciones[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
