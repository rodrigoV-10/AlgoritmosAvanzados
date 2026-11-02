#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Tarea {
    char id;
    int tiempo;
    int peso;
};

//minimizar el costo ponderado
//una tarea es rentable si
//tiene mucho peso y consume poco tiempo peso/tiempo
bool compara(Tarea a, Tarea b) {
    double ratioA = a.peso/a.tiempo;
    double ratioB = b.peso/b.tiempo;
    if (ratioA != ratioB)
        return ratioA > ratioB;
    else
        return a.tiempo<b.tiempo;
}

void scheduling_tiempos(vector<Tarea>&tareas,int n) {
    sort(tareas.begin(), tareas.end(), compara);
    int tiempo=0;
    int ponderadoTotal=0;
    cout<<"Ordenamiento final segun regla de smith"<<endl;
    for (int i=0; i<n; i++) {
        cout<<"Tarea: "<<tareas[i].id<<endl;
        cout<<"Tiempo procesamiento: "<<tareas[i].tiempo<<endl;
        cout<<"Peso: "<<tareas[i].peso<<endl;
        double ratio = (double) tareas[i].peso/tareas[i].tiempo;
        cout<<"Ratio: "<<ratio<<endl;
        tiempo+=tareas[i].tiempo;
        cout<<"Completion Time: "<<tiempo<<endl;
        double ponderado = tareas[i].peso*tiempo;
        ponderadoTotal+=ponderado;
        cout<<"Costo ponderado: "<<ponderado<<endl;
        cout<<"-----------------------------"<<endl;
    }
    cout<<"Costo total ponderado: "<<ponderadoTotal<<endl;
}

int main() {
    vector<Tarea> tareas = {
        {'A',4,20},
        {'B',2,10},
        {'C',5,15},
        {'D',3,18},
    };
    int n = tareas.size();
    scheduling_tiempos(tareas, n);

    return 0;
}
