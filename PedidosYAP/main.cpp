#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

#define MAX 8

using namespace std;


struct nodo {
    int punto=0;
    int distancia=0;
};

//llegar en poco tiempo a un punto determinado
bool compara(nodo a , nodo b) {
    return a.distancia < b.distancia;
}



int rutaMin(int inicio,int fin,int mapa[][MAX]) {
    int ciudad=inicio;
    int total=0;
    while (true) {
        vector<nodo> vecinos;
        nodo paso;
        for (int i=0; i<MAX; i++) {
            //si hay conexion guardo ese valor
            if (mapa[ciudad][i]!=0) {
                paso.punto = i;
                paso.distancia=mapa[ciudad][i];
                vecinos.push_back(paso);
            }
        }
        //mientras tenga vecinos que recorrer
        if (!vecinos.empty()) {
            sort(vecinos.begin(), vecinos.end(), compara);
            ciudad=vecinos[0].punto; //actualizar la posicion actual
            //me muevo a la ciudad más cercana
            total+=vecinos[0].distancia; //guardo el valor
        }
        if (ciudad==fin) break; //si llegamos al fin salimos del bucle
        if (vecinos.empty()) {
            cout<<"No existe solucion"<<endl;
            total=0;
            break;
        }
    }
    return total;
}



int main() {
    int mapa [][MAX]={
        //A , B , C , D , E , F , G, H
        {0,4,  5,  6, 0 ,  0,  0 , 0}, //A
        {0,0,  0,  0, 2 ,  0,  0 , 0}, //B
        {0,0,  0,  0, 0 ,  0,  0 , 3}, //C
        {0,0,  0,  0, 0 ,  3,  0 , 0}, //D
        {0,0,  0,  0, 0 ,  0,  10 , 0}, //E
        {0,0,  0,  0, 0 ,  0,  2 , 0}, //F
        {0,0,  0,  0, 0 ,  0,  0 , 0}, //G
        {0,0,  0,  0, 0 ,  0,  0 , 0}, //H
    };
    //datos de entrada punto de partida A y llegada G
    cout<<rutaMin(0,6,mapa)<<endl;


    return 0;
}
