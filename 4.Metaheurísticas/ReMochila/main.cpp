#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>
#include <ctime>

#define ALFA 0.3
#define ITERACIONES 10000

using namespace std;

//como es minimizar es ascendete
bool compara(int a, int b) {
    return a < b;
}

int contarSoluciones(vector<int> paquetes,int RCL) {
    int contador=0;
    for (int i = 0; i < paquetes.size(); i++) {
        if (paquetes[i]<=RCL) {
            contador++;
        }
    }
    return contador;
}

void graspMochilon(int *paq,int n,int peso) {
    vector<int> mejorSolucion;
    srand(time(NULL));
    int mejor=INT_MAX;
    for (int i=0; i<ITERACIONES; i++) {
        vector<int> soluciones;
        vector<int> paquetes;
        paquetes.insert(paquetes.begin(),paq,paq+n);
        sort(paquetes.begin(),paquetes.end(),compara);
        int residual=peso;
        //mientras no este vacio entonces vamos a la fase de construccion
        while (!paquetes.empty()) {
            int BETA = paquetes[0];
            int TAO = paquetes[paquetes.size()-1];
            double minRCL = BETA+ALFA*(TAO-BETA);
            int cantidad_RCL = contarSoluciones(paquetes,minRCL);
            if (cantidad_RCL==0) {
                break;
            }
            int indiceAleatorio= rand()%cantidad_RCL;
            if (residual-paquetes[indiceAleatorio]>=0) {
                residual-=paquetes[indiceAleatorio];
                soluciones.push_back(paquetes[indiceAleatorio]);
            }
            paquetes.erase(paquetes.begin()+indiceAleatorio);
        }
        //imprimimos soluciones
        for (int i=0; i<soluciones.size(); i++) {
            cout<<soluciones[i]<<" ";
        }
        cout<<endl<<residual<<endl;
        //ahora calculamos la mejor solucion
        if (residual<mejor) {
            mejor = residual;
            mejorSolucion.clear();
            mejorSolucion.insert(mejorSolucion.begin(),soluciones.begin(),soluciones.end());
        }
    }
    cout<<"Mejor solucion"<<endl;
    for (int i=0; i<mejorSolucion.size(); i++) {
        cout<<mejorSolucion[i]<<" ";
    }
    cout<<endl<<mejor<<endl;
}

int main() {
    //problema de la mochila :)
    int paq[]={14,12,15,14,20,11,5,17,14,28,15,27,12,10,30,16,10};
    int peso=33;
    int n = sizeof(paq)/sizeof(paq[0]);
    graspMochilon(paq,n,peso);
    //tratamos de minimizar

    return 0;
}
