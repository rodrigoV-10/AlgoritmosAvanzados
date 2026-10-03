#include <iostream>
#include <climits>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>


#define ALFA 0.4
#define ITERACIONES 10000

using namespace std;

struct SNodo {
    char nombre;
    int ganancia;
};

struct Candidato {
    int id;
    int ganancia;
};

//debemos maximizar la ganancia
bool comparar(Candidato a, Candidato b) {
    return a.ganancia > b.ganancia;
}

int buscarRCL(double RCL,vector<Candidato> &candidatos) {
    int cont = 0;
    for (int i=0;i<candidatos.size();i++ ) {
        if (candidatos[i].ganancia >= RCL) {
            cont++;
        }
    }
    return cont;
}

void rutaYAP(vector<vector<int>>&matriz,vector<SNodo>&nodos) {
    int mejor = INT_MIN;
    vector<char> mejor_solucion;
    int n_nodos = matriz.size();
    //cout << n_nodos << endl;
    srand(time(NULL));
    for (int i=0; i<ITERACIONES; i++) {
        int nodo_actual = 0; //empezamos del nodo A
        int ganancia_actual = 0;
        vector<char> solucion;
        vector<Candidato> candidatos;
        //candidatos iniciales
        //cumple el rol del insert
        for (int j=0; j<n_nodos; j++) {
            if (matriz[nodo_actual][j]==1) {
                candidatos.push_back({j,nodos[j].ganancia});
            }
        }
        while (!candidatos.empty()) {
            sort(candidatos.begin(), candidatos.end(),comparar);
            int BETA = candidatos[0].ganancia;
            int TAO = candidatos[candidatos.size()-1].ganancia;
            double RCL = BETA-ALFA*(BETA-TAO);
            int rangoRCL = buscarRCL(RCL,candidatos);
            int indiceAleatorio = rand()%rangoRCL;
            int siguienteNodo = candidatos[indiceAleatorio].id;
            //actualizamos
            ganancia_actual+=nodos[siguienteNodo].ganancia;
            solucion.push_back(nodos[siguienteNodo].nombre);
            nodo_actual = siguienteNodo;
            candidatos.clear();
            // ACTUALIZAMOS los candidatos para la siguiente vuelta del while
            for (int j=0; j<n_nodos; j++) {
                if (matriz[nodo_actual][j]==1) {
                    candidatos.push_back({j,nodos[j].ganancia});
                }
            }
        }
        if (ganancia_actual>mejor) {
            mejor = ganancia_actual;
            mejor_solucion = solucion;
        }
    }
    cout<<"Ganancia = "<<mejor<<endl;
    cout<<"Camino : ";
    for (int i=0; i<mejor_solucion.size(); i++) {
        cout<<mejor_solucion[i]<<" ";
    }
    cout<<endl;
}

int main() {

    vector<SNodo> nodos={
        {'A',0},
        {'B',20},
        {'C',30},
        {'D',40},
        {'E',40},
        {'F',40},
        {'G',10},
        {'H',50},
    };


    vector<vector<int>>matriz={
        //A B C D E F G H
        { 0, 1, 1, 1, 1, 0, 0, 1 }, // A
        { 0, 0, 1, 1, 0, 1, 0, 1 }, // B
        { 0, 0, 0, 0, 0, 1, 0, 0 }, // C
        { 0, 0, 0, 0, 0, 0, 0, 0 }, // D
        { 0, 0, 1, 0, 0, 1, 1, 0 }, // E
        { 0, 0, 0, 0, 0, 0, 0, 0 }, // F
        { 0, 0, 0, 0, 0, 0, 0, 0 }, // G
        { 0, 0, 0, 0, 0, 0, 0, 0 }  // H
    };

    rutaYAP(matriz,nodos);

    return 0;
}
