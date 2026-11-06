#include <iostream>
#include <random>
#include <climits>
#include <vector>
#include <algorithm>

#define ITERACIONES 10000
#define ALFA 0.3
#define COSTO_MAX 20
#define N 4
#define M 5

using namespace std;

struct Ciudad {
    char id;
    int costo;
};

struct Motorizado {
    int id;
    int costo;
};

struct Asignacion {
    char ciudad;
    int motorizado;
    int costoTotal;
};

bool compara(Motorizado a, Motorizado b) {
    return a.costo<b.costo;
}

int buscarRCL(double RCL,vector<Motorizado>candidatos) {
    int cantidad=0;
    for (int i=0;i<candidatos.size();i++) {
        if (candidatos[i].costo<=RCL) {
            cantidad++;
        }
    }
    return cantidad;
}


//se desea minimizar los costos de sus envios a diversar ciudades
//se tiene dos costos
//el primero es el mayor monto que esta dado por el transporte a la ciudad
//una vez que llega el paquete se contrata un servicio que tiene diversos valores
//se decicio que el costo de los envios no debe de pasar un valor k soles

void grasp(vector<Ciudad>&ciudades,int matriz_costos[M][N]) {
    vector<Asignacion> mejorSolucion;
    int mejor = INT_MAX;
    srand(time(NULL));
    for (int i=0;i<ITERACIONES;i++) {
        vector<Asignacion> unaSolucion;
        int acumulado=0;
        //recorremos las ciudades
        for (int j=0;j<N;j++) {
            vector<Motorizado> candidatos;
            //buscamos los motorizados validos que no pasen el valor de "K"
            for (int k=0;k<M;k++) {
                int total = ciudades[j].costo+matriz_costos[k][j];
                if (total<=COSTO_MAX) {
                    candidatos.push_back({k+1,matriz_costos[k][j]});
                }
            }

            if (candidatos.empty()) break;
            sort(candidatos.begin(),candidatos.end(),compara);
            int beta = candidatos[0].costo;
            int tao = candidatos[candidatos.size()-1].costo;
            double RCL = beta+ALFA*(tao-beta);
            int cantidad_rcl=buscarRCL(RCL,candidatos);
            int indiceAleatorio = rand()%cantidad_rcl;

            //Motorizado seleccionado de manera aleatoria
            Motorizado seleccionado;
            seleccionado = candidatos[indiceAleatorio];
            int costoTotal = ciudades[j].costo+seleccionado.costo;
            unaSolucion.push_back({ciudades[j].id,seleccionado.id,costoTotal});
            acumulado+=costoTotal;

        }
        if (acumulado<mejor) {
            mejor= acumulado;
            mejorSolucion.clear();
            mejorSolucion=unaSolucion;
        }
    }
    cout<<"Mejor costo: "<<mejor<<endl;

    for (int i=0;i<mejorSolucion.size();i++) {
        cout<<"Ciudad "<<mejorSolucion[i].ciudad
            <<" - Motorizado "<<mejorSolucion[i].motorizado
            <<" - Costo "<<mejorSolucion[i].costoTotal
            <<endl;
    }
}



int main() {
    vector<Ciudad> ciudades={
        {'A',16},
        {'B',15},
        {'C',12},
        {'D',18}
    };

    int costos[M][N]={
        {3,4,5,6},
        {5,2,3,4},
        {7,5,4,2},
        {8,7,5,1},
        {4,3,7,5}
    };


    grasp(ciudades,costos);







    return 0;
}
