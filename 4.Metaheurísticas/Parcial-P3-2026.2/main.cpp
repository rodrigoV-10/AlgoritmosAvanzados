#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define N 7
using namespace std;


struct Antena {
    int indice;
    int grado;
};

bool compara(Antena a, Antena b) {
    if (a.grado != b.grado) {
        //descendente de acuerdo al de mayor grado
        return a.grado > b.grado;
    }else {
        //el de menor indice
        return a.indice < b.indice;
    }
}

bool esValido(int pos,int canal,int grafo[N][N],vector<int>frecuencias) {
    for (int i=0;i<N;i++) {
        if (grafo[pos][i] == 1 and frecuencias[i] == canal) {
            return false;
        }
    }
    return true;
}

void grafosDeTupia(int grafo[N][N],vector<int>&frecuencias) {
    //tenemos que utilizar una especie de ordenamiento para ello ordenamos los que tienen una gran cantidad
    //de conexiones
    vector<Antena> antenas;
    for (int i=0;i<N;i++) {
        int conexiones=0;
        for (int j=0;j<N;j++) {
            if (grafo[i][j]==1) {
                conexiones++;
            }
        }
        antenas.push_back({i,conexiones});
    }
    sort(antenas.begin(),antenas.end(),compara);
    int canalesUsados=0;
    for (int pos=0; pos<N; pos++) {
        int antena = antenas[pos].indice;
        for (int canal=1;canal<=canalesUsados+1;canal++) {
            if (esValido(antena,canal,grafo,frecuencias)) {
                frecuencias[antena]=canal;
                if (canal>canalesUsados) {
                    canalesUsados=canal;
                }
                break;
            }

        }
    }
}

int main() {
    // Antenas A, B, C, D, E, F, G
    int grafo[N][N] = {
        {0,1,1,1,0,0,0},
        {1,0,1,0,1,0,0},
        {1,1,0,0,0,1,0},
        {1,0,0,0,0,0,1},
        {0,1,0,0,0,0,0},
        {0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0}
    };
    //todos no tienen ningun color asignado al inicio
    vector<int>frecuencias(N,0);
    //queremos minimizar la cantidad de canales

    grafosDeTupia(grafo,frecuencias);

    for (int i=0; i<frecuencias.size(); i++) {
        cout<<"Antena "<<char('A'+i)<<" ";
        cout<<frecuencias[i]<<endl;
    }

    return 0;
}
