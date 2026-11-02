#include <iostream>
#include <vector>
using namespace std;

void bactrack_combinatorias(int idx,int acumulado,int k,
    vector<int> &cantidatos,vector<int>&unaSolucion,
    vector<vector<int>>&soluciones) {
    if (acumulado==k) {
        soluciones.push_back(unaSolucion);
        return;
    }
    if (acumulado>k) return;
    for (int i = idx; i<cantidatos.size(); i++) {
        unaSolucion.push_back(cantidatos[i]);
        bactrack_combinatorias(i,acumulado+cantidatos[i],k,cantidatos,
            unaSolucion,soluciones);
        unaSolucion.pop_back();
    }
}


int main() {
    vector<int> cantidatos = {2,3,6,7};
    int k = 7; //objetivo que tenemos que llegar
    //aqui podemos utilizar el mismo número varias veces
    //ejemplo 2 + 2 + 3 , 7

    //le envio la pos actual , la suma hasta el momento = 0 , la restriccion y el vector
    vector<vector<int>>soluciones;
    vector<int>unaSolucion;
    bactrack_combinatorias(0,0,k,cantidatos,unaSolucion,soluciones);
    for (int i=0;i<soluciones.size();i++) {
        for (int j=0;j<soluciones[i].size();j++) {
            cout << soluciones[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
