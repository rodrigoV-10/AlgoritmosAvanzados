#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define MAX 8

using namespace std;

struct nodo {
    int punto;
    int distancia;
};

bool compara(nodo a, nodo b) {
    return a.distancia < b.distancia;
}

int rutamin(int inicio,int fin,int mapa[][MAX]) {
    int ciudad=inicio;
    int total=0;
    vector<bool> visitado(MAX,false);
    visitado[ciudad]=true;
    while(ciudad!=fin) {
        //primero chapo los vecinos de donde me encuentro
        vector<nodo> vecinos;
        for (int i=0; i<MAX ; i++) {
            //si hay conexion con esa ciudad
            //y si no ha sido visitado
            if (mapa[ciudad][i]!=0 && !visitado[i]) {
                //guardo sus datos
                nodo paso{};
                paso.punto=i;
                paso.distancia=mapa[ciudad][i];
                vecinos.push_back(paso);
            }
        }
        //afuera del for ordeno de menor a mayor la distancia con cada ciudad
        if (vecinos.empty()) {
            cout<<"No se encontró solucion"<<endl;
            return 0;
        }
        sort(vecinos.begin(),vecinos.end(),compara);
        ciudad=vecinos.front().punto;
        total+=vecinos.front().distancia;
        visitado[ciudad]=true;
    }
    return total;
}

int main() {
    int mapa[][MAX] {   {0,4,5,6,0,0,0,0},
                    {0,0,0,0,2,0,0,0},
                    {0,0,0,0,0,0,0,3},
                    {0,0,0,0,0,3,0,0},
                    {0,0,0,0,0,0,10,0},
                    {0,0,0,0,0,0,2,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};

    cout<<"La ruta obtenida es: "<<rutamin(0,6,mapa)<<endl;
    return 0;
}
