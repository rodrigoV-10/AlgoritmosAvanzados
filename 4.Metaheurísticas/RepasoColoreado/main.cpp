#include <iostream>
#include <vector>
#include <algorithm>
#define N 7

#define ROJO 1
#define VERDE 2
#define AZUL 3

using namespace std;

bool esValido(vector<int>prohibido,vector<int>frecuencias,int antena,int color,int grafo[N][N]) {
    //si tiene un color prohibido no es una solucion
    if (prohibido[antena]==color) {
        return false;
    }
    //recorremos sus vecinos y verificamos que no tengan el mismo color
    for (int i=0;i<N; i++) {
        //si tiene conexion y veo que sus vecinos tienen el mismo color
        if (grafo[antena][i]==1 and frecuencias[i]==color) {
            return false;
        }
    }
    return true;
}


bool esPintable(int grafo[N][N],vector<int>&frecuencias,vector<int>prohibido) {
    //recorremos las antenas
    for (int antena=0;antena<N;antena++) {
        //verificamos las antenas con colores fijos
        if (frecuencias[antena]!=0) {
            //si no es valido entonces salimos del bucle
            if (!esValido(prohibido,frecuencias,antena,frecuencias[antena],grafo)) {
                return false;
            }else {
                continue;
            }
        }

        for (int i=1; i<=3 ; i++) {
            if (esValido(prohibido,frecuencias,antena,i,grafo)) {
                frecuencias[antena]=i;
                break;
            }
        }

        //si no se pudo asignar un colro a nuestra antena actual entonces no hay solucion
        if (frecuencias[antena]==0) {
            return false;
        }
    }
    return true;
}

int main() {
    int grafo[N][N] = {
        {0,1,1,0,0,0,0},
        {1,0,1,1,0,0,0},
        {1,1,0,1,1,0,0},
        {0,1,1,0,1,1,0},
        {0,0,1,1,0,1,1},
        {0,0,0,1,1,0,1},
        {0,0,0,0,1,1,0}
    };
    vector<int>frecuencias = {1,0,0,0,2,0,0};
    vector<int>prohibido =   {0,0,0,0,0,ROJO,0};

    if (esPintable(grafo,frecuencias,prohibido)) {
        for (int i=0;i<N;i++) {
            cout<<frecuencias[i]<<" ";
        }
    }else {
        cout<<"No existe solucion"<<endl;
    }

    return 0;
}
