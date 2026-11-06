#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generarPermutaciones(int n,int aperturas,int cierres,
    string &actual,vector<string>&soluciones) {
    //condicion de parada del problema
    if (actual.size()==2*n) {
        soluciones.push_back(actual);
        return;
    }
    //agregar (
    if (aperturas<n) {
        actual.push_back('(');
        generarPermutaciones(n,aperturas+1,cierres,actual,soluciones);
        actual.pop_back();
    }
    if (cierres<aperturas) {
        actual.push_back(')');
        generarPermutaciones(n,aperturas,cierres+1,actual,soluciones);
        actual.pop_back();
    }

    //agregar )
}


int main() {

    int n=3;
    //int longitud = pow(2,n);

    string actual="";
    vector<string> soluciones;
    generarPermutaciones(n,0,0,actual,soluciones);
    for (int i=0;i<soluciones.size();i++) {
        cout<<soluciones[i]<<endl;
    }


    return 0;
}