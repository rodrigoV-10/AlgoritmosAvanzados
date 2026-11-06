#include <iostream>
#include <vector>

#define ROJO  1
#define VERDE 2
#define AZUL  3

#define N 7
#define K 3

using namespace std;

bool esValido(int antena,int color,int grafo[N][N],
    vector<int>&frecuencias,vector<int>prohibido) {
    if (prohibido[antena]==color) {
        return false;
    }
    //revisamos los vecinos
    for (int i=0; i<N ; i++) {
        //si tienen conexion, pero tienen el mismo color
        //retornamos falso
        if (grafo[antena][i]==1 and frecuencias[i]==color) {
            return false;
        }
    }
    return true;
}

bool coloreadoVoraz(int grafo[N][N],vector<int>&frecuencias,
    vector<int>prohibido) {
    //recorremos los nodos
    for (int antena=0;antena<N;antena++) {
        //vemos los colores
        //si tiene color fijo entonces
        //si es diferente de 0 entonces ya se le asignó un color
        if (frecuencias[antena]!=0) {
            //supongamos que la antena 4 tiene
            //frecuencia VERDE
            //LA FRECUENCIA VERDE QUE TIENE LA ANTENA 4 ES VALIDA PARA SUS VECINOS?
            //si es que no entonces retornamos falso
            if (!esValido(antena,frecuencias[antena],grafo,frecuencias,prohibido)) {
                return false;
            }
            //caso contrario pasamos a la otra iteracion
            continue;
        }
        bool asignado=false;

        //probamos los colores disponibles
        for (int color=1; color<=K ; color++) {
            if (esValido(antena,color,grafo,frecuencias,prohibido)) {
                frecuencias[antena]=color;
                asignado=true;
                break; //ya encontramos un color valido
            }
        }
        //si no se pudo asignar ningun color
        if (!asignado) {
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
    if (coloreadoVoraz(grafo,frecuencias,prohibido)) {
        for (int i=0; i<frecuencias.size(); i++) {
            cout << frecuencias[i] << " ";
        }
    }
    return 0;
}
