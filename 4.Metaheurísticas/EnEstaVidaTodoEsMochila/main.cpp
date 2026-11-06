#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#define ITERACIONES 10000
#define ALFA 0.3

using namespace std;

bool compara(int a,int b) {
    return a>b;
}

//como tratamos de minimizar entonces paq[i]<=maxRCL
int buscarIndice(vector<int>paquete,double maxRCL) {
    int cont=0;
    for (int i=0;i<paquete.size();i++) {
        if (paquete[i]<=maxRCL) {
            cont++;
        }
    }
    return cont;
}

void ustedesParaSusViejosSonUnaMochila(int *paq,int peso,int n) {
    vector<int> mejorSolucion;
    int mejor = INT_MAX;
    srand(time(NULL));
    for(int i=0;i<ITERACIONES;i++) {
        //una solucion
        vector<int>solucion;
        vector<int>paquete;
        //tratamos de minimizar
        sort(paquete.begin(),paquete.end(),compara);
        paquete.insert(paquete.begin(),paq,paq+n);
        int residuo = peso;
        while (!paquete.empty()) {
            //este es el esquema genérico del programa
            int beta = paquete[0];
            int tao = paquete[paquete.size()-1];
            //cambia dependiendo si quiero minimizar o maximizar
            double maxRCL = beta+ALFA*(tao-beta);
            //aquí entra lo randonomico
            int cantidadRCL =  buscarIndice(paquete,maxRCL);
            int indiceAleatorio = rand()%cantidadRCL;
            //esto depende del problema pues cada problema presenta contextos diferentes
            if (residuo-paquete[indiceAleatorio]>=0) {
                solucion.push_back(paquete[indiceAleatorio]);
                residuo -= paquete[indiceAleatorio];
            }
            //una vez se asigna un valor realizamos el erase
            paquete.erase(paquete.begin()+indiceAleatorio);
        }
        // for (int j=0;j<solucion.size();j++) {
        //     cout << solucion[j] << " ";
        // }
        // cout << endl << residuo << endl;

        //OJO: Esto corresponde a una iteración por ello iteramos varias veces
        //comparamos para guardar la solucion
        if (residuo<mejor) {
            //actualizamos el mejor residuo
            mejor=residuo;
            //borramos la solucion anterior si es que la había
            mejorSolucion.clear();
            //actualizamos nuestra mejor solucion
            mejorSolucion.insert(mejorSolucion.begin(),solucion.begin(),solucion.end());
        }
    }
    cout<<"Mejor solucion obtenida: "<<endl;
    for (int i=0;i<mejorSolucion.size();i++) {
        cout << mejorSolucion[i] << " ";
    }
    cout<<endl<<mejor<<endl;

}


int main() {
    int paq[] = {14,12,15,14,20,11,5,17,14,28,15,27,12,10,30,16,10};
    int peso = 33;
    int n = sizeof(paq)/sizeof(paq[0]);
    ustedesParaSusViejosSonUnaMochila(paq,peso,n);
    return 0;
}
