#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Objeto {
    int id;
    int peso;
};

//2 criterios para la asignacion
//el primero considera que los mejores paquetes son de mayor peso
//el segundo es que el mejor camion es el que tiene capacidad para
//transportar el minimo peso con el fin de no desperdiciar espacio
bool comparaPaquete(Objeto a, Objeto b) {
    return a.peso > b.peso;
}

bool comparaCamion(Objeto a,  Objeto b) {
    return a.peso < b.peso;
}


void tupiaTE_CHAPAo_o(vector<Objeto>&paquetes,vector<Objeto>&camiones,
    int n,int m) {
    sort(paquetes.begin(),paquetes.end(),comparaPaquete);
    sort(camiones.begin(),camiones.end(),comparaCamion);
    vector<vector<int>> soluciones(m+1);
    //recorremos los paquetes
    for (int i=0;i<n;i++) {
        int peso = paquetes[i].peso;
        int id = paquetes[i].id;
        //recorremos los camiones
        for (int j=0;j<m;j++) {
            if (peso<=camiones[j].peso) {
                //actualizamos el peso
                camiones[j].peso -= peso;
                soluciones[camiones[j].id].push_back(id);
                break;
            }
        }
    }

    for (int i=1;i<=m;i++) {
        cout<<"Camion "<<i<<" : ";
        for (int j=0;j<soluciones[i].size();j++) {
            cout << soluciones[i][j]<<" ";
        }
        cout << endl;
    }

}

int main() {
    vector<Objeto> paquetes={
        {1,150},
        {2,100},
        {3,180},
        {4,50},
        {5,120},
        {6,10},
    };
    vector<Objeto> camiones ={
        {1,250},
        {2,200},
        {3,200},
        {4,100},
        {5,300},
    };
    int n = paquetes.size();
    int m = camiones.size();

    tupiaTE_CHAPAo_o(paquetes,camiones,n,m);

    return 0;
}
