#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>

#define ITERACIONES 10000
#define ALFA 0.4
#define N 8

using namespace std;

struct Entrega {
    int pos;
    char id;
    int pago;
};


bool compara(Entrega a, Entrega b) {
    return a.pago>b.pago;
}

int buscarRCL(double RCL,vector<Entrega>arreglo) {
    int cont=0;
    for (int i=0; i<arreglo.size(); i++) {
        if (arreglo[i].pago>=RCL) {
            cont++;
        }
    }
    return cont;
}

void grasp(int grafo[N][N],vector<Entrega>&entregas) {
    int n = entregas.size();
    srand(time(NULL));
    vector<char>mejorSolucion;
    //quiero tener la mejor ganancia
    int mejor=INT_MIN;
    for (int i=0;i<ITERACIONES;i++) {
        int posActual=0;
        vector<bool> visitados(N,false);
        visitados[posActual]=true;
        vector<char>unaSolucion;
        int acumulado=0;
        while (!entregas.empty()) {
            //recorrido del grafo para obtener la mejor ganancia
            vector<Entrega> vecinos;
            for (int k=0;k<N ; k++) {
                //hay conexion y no ha sido visitado
                if (grafo[posActual][k]==1 and !visitados[k]) {
                    vecinos.push_back(entregas[k]);
                }
            }
            if (vecinos.empty()) {
                break;
            }

            sort(vecinos.begin(),vecinos.end(),compara);
            int beta = vecinos[0].pago;
            int tao = vecinos[vecinos.size()-1].pago;
            double RCL = beta-ALFA*(beta-tao);
            int cantidad_RCL = buscarRCL(RCL,vecinos);
            if (cantidad_RCL==0) break;
            int indiceAleatorio = rand()%cantidad_RCL;

            posActual=vecinos[indiceAleatorio].pos;
            acumulado+=vecinos[indiceAleatorio].pago;
            unaSolucion.push_back(vecinos[indiceAleatorio].id);
            visitados[posActual]=true;
            vecinos.erase(vecinos.begin()+indiceAleatorio);
            sort(vecinos.begin(),vecinos.end(),compara);
        }
        if (acumulado>mejor) {
            mejor=acumulado;
            mejorSolucion.clear();
            mejorSolucion=unaSolucion;
        }
    }

    for (int i=0; i<mejorSolucion.size(); i++) {
        cout<<mejorSolucion[i]<<" ";
    }
    cout<<endl<<mejor<<endl;
}

int main() {
    int grafo[N][N] = {
        // A B C D E F G H
        { 0,1,1,1,1,0,0,1 }, // A
        { 0,0,1,1,0,1,0,1 }, // B
        { 0,0,0,0,0,1,0,0 }, // C
        { 0,0,0,0,0,0,0,0 }, // D
        { 0,0,1,0,0,1,1,0 }, // E
        { 0,0,0,0,0,0,0,0 }, // F
        { 0,0,0,0,0,0,0,0 }, // G
        { 0,0,0,0,0,0,0,0 }  // H
    };
    //pos 1 = A  . . .
    vector<Entrega> entregas={
        {0,'A',0},
        {1,'B',20},
        {2,'C',30},
        {3,'D',40},
        {4,'E',40},
        {5,'F',40},
        {6,'G',10},
        {7,'H',50}
    };

    grasp(grafo,entregas);

    return 0;
}
