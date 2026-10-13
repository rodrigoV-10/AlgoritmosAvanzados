#include <iostream>
#include <vector>

#define ROJO  1
#define VERDE 2
#define AZUL  3

#define N 7
#define K 3

using namespace std;

bool esValido(int antena,int color,int grafo[N][N],
    vector<int>&frecuencias,vector<int>&prohibido) {
    //si tiene el color que esta prohibido retornamos falso
    if (prohibido[antena]==color) {
        return false;
    }
    //revisamos a los vecinos
    for (int i=0 ; i<N;i++) {
        //preguntamos si hay conexion
        //la antena i tiene el color que queremos utilzar?
        if (grafo[antena][i]==1 and frecuencias[i]==color) {
            return false;
        }
    }
    //caso contrario retorna verdadero
    return true;
}

bool backtrackGrafo(int antena,int grafo[N][N],vector<int>&frecuencias,
    vector<int>&prohibido) {
    if (antena==N) {
        return true; //ya recorrimos todos
    }
    
    //si tiene una frecuencia asignada no modificarla
    if (frecuencias[antena]!=0) {
        if (!esValido(antena,frecuencias[antena],grafo,frecuencias,prohibido)) {
            return false;
        }
        return backtrackGrafo(antena+1,grafo,frecuencias,prohibido);
    }
    for (int i=1; i<=K ; i++) {
        if (esValido(antena,i,grafo,frecuencias,prohibido)) {
            frecuencias[antena]=i;
            if (backtrackGrafo(antena+1,grafo,frecuencias,prohibido)) {
                return true;
            }
            frecuencias[antena]=0;
        }
    }
    return false;
}

int main() {
    //cada vertice representa una antena
    //cada arista indica que existe interferencia entre dos antenas
    //cada antena debe tener una frecuencia
    //dos antenas conectadas no pueden tener la misma frecuencia
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
    //la antena 5 no puede utilizar frencuencia roja
    if (backtrackGrafo(0,grafo,frecuencias,prohibido)) {
        for (int i=0;i<frecuencias.size();i++) {
            cout << frecuencias[i] << " ";
        }
    }
    return 0;
}
