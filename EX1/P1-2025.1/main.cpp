#include <iostream>
#include <vector>
#define N 6
using namespace std;

void generaRutas(int partida,double acumulado,double &tope,
    vector<bool>&visitado,double matriz[][N],vector<int>&ruta,
    vector<int>&mejorRuta) {
    if (ruta.size()==N) {
        int ultimo = ruta.back();
        double distanciaTotal = acumulado+matriz[ultimo][0];
        if (distanciaTotal<tope) {
            tope = distanciaTotal;
            mejorRuta = ruta;
        }
        return;
    }

    for (int i=0;i<N;i++) {
        if (!visitado[i] and matriz[partida][i]!=0) {
            visitado[i] = true;
            ruta.push_back(i);
            acumulado+=matriz[partida][i];
            generaRutas(i,acumulado,tope,visitado,matriz,ruta,mejorRuta);
            acumulado-=matriz[partida][i];
            ruta.pop_back();
            visitado[i] = false;
        }
    }
}


int main() {
    double matriz[N][N] = {
        {0.00, 2.24, 2.69, 4.00, 2.06, 3.35},//DESTINO 0
        {2.24, 0.00, 4.50, 5.39, 1.50, 5.59},//DESTINO 1
        {2.69, 4.50, 0.00, 5.59, 4.74, 2.55},//DESTINO 2
        {4.00, 5.39, 5.59, 0.00, 4.03, 3.91},//DESTINO 3
        {2.06, 1.50, 4.74, 4.03, 0.00, 5.10},//DESTINO 4
        {3.35, 5.59, 2.55, 3.91, 5.10, 0.00},//DESTINO 5
    };

    vector<bool> visitado(N,false);
    vector<int> ruta;
    ruta.push_back(0);
    vector<int> mejorRuta;
    visitado[0] = true;
    double acumulado=matriz[0][0];
    double tope=INT_MAX;
    generaRutas(0,acumulado,tope,visitado,matriz,ruta,mejorRuta);
    for (int i=0;i<N;i++) {
        cout << mejorRuta[i] << " ";
    }
    cout<<"(distancia "<<tope<<")"<<endl;


    return 0;
}
