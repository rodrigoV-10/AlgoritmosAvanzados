#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#define ITERACIONES 10000
#define ALFA 0.3

#define PRESUPUESTO 400

using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    vector<int>predecesores;
};

struct Seleccionado {
    vector<int>seleccionados;
    int beneficioTotal;
};

bool esValido(vector<int>unaSolucion,Proyecto unProyecto) {
    if (unProyecto.predecesores.size() == 0) {
        return true;
    }
    int cont=0;
    for (int i=0; i<unaSolucion.size(); i++) {
        for (int j=0; j<unProyecto.predecesores.size(); j++) {
            if (unaSolucion[i] == unProyecto.predecesores[j]) {
               cont++;
            }
        }
    }
    if (cont==unProyecto.predecesores.size()) {
        return true;
    }
    return false;
}

double calcularHeuristica(Proyecto p) {
    return p.ganancia/(double)p.costo;
}

//maximizar la ganancia
bool compara(Proyecto a, Proyecto b) {
    return calcularHeuristica(a)>calcularHeuristica(b);
}

int calcularRCL(double RCL,vector<Proyecto>candidatos) {
    int cont=0;
    for (int i=0; i<candidatos.size(); i++) {
        if (calcularHeuristica(candidatos[i])>=RCL) {
            cont++;
        }
    }
    return cont;
}

void grasp(vector<Proyecto>proyectos) {
    srand(time(NULL));
    int mejor=INT_MIN;
    vector<int>mejorSolucion;
    for(int i=0;i<ITERACIONES;i++) {
        int acumulado=0;
        int tope=PRESUPUESTO;
        vector<int> unaSol;
        vector<Proyecto> arreglo_proyectos;
        arreglo_proyectos=proyectos;
        sort(arreglo_proyectos.begin(),arreglo_proyectos.end(),compara);
        while (!arreglo_proyectos.empty()) {
            vector<Proyecto> candidatos;
            //contiene los proyectos que podemos seleccionar en este momento
            for (int j=0; j<arreglo_proyectos.size(); j++) {
                if (esValido(unaSol,arreglo_proyectos[j]) and
                    tope-arreglo_proyectos[j].costo>=0) {
                    candidatos.push_back(arreglo_proyectos[j]);
                }
            }
            if (candidatos.size()==0) break;
            sort(candidatos.begin(),candidatos.end(),compara);
            double beta = calcularHeuristica(candidatos[0]);
            double tao = calcularHeuristica(candidatos[candidatos.size()-1]);
            double RCL = beta-ALFA*(beta-tao);
            int umbral = calcularRCL(RCL,candidatos);
            if (umbral==0) break;
            int indiceAleatorio = rand()%umbral;
            Proyecto proyecto_aleatorio = candidatos[indiceAleatorio];

            unaSol.push_back(proyecto_aleatorio.id);
            tope-=proyecto_aleatorio.costo;
            acumulado+=proyecto_aleatorio.ganancia;

            //se elimina el proyecto que acabamos de seleccionar
            for (int j=0; j<arreglo_proyectos.size(); j++) {
                if (arreglo_proyectos[j].id==proyecto_aleatorio.id) {
                    arreglo_proyectos.erase(arreglo_proyectos.begin()+j);
                    break;
                }
            }

        }

        if (mejor<acumulado) {
            mejor=acumulado;
            mejorSolucion.clear();
            mejorSolucion=unaSol;
        }
    }


    for (int i=0; i<mejorSolucion.size(); i++) {
        cout << mejorSolucion[i] << " ";
    }
    cout << endl << mejor << endl;
}




int main() {
    vector<Proyecto> proyectos={
        {1,100,200,{}},
        {2,50 ,300,{1}},
        {3,150,300,{1}},
        {4,50 ,400,{}},
        {5,50 ,200,{4}},
        {6,150,800,{2,4}},
        {7,100,250,{}},
    };
    grasp(proyectos);

    return 0;
}
