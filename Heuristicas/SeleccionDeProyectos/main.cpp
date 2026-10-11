#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <complex>
#define N 8

using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int> predecesores;
};

//para la seleccion de proyectos se debe de maximizar la ganancia
//y el beneficio , minimizando el costo
bool compara(Proyecto a, Proyecto b) {
    return (double)(a.ganancia*a.beneficio)/a.costo > (double)(b.ganancia*b.beneficio)/b.costo;
}

bool cumpleDependencias(Proyecto p,vector<bool> seleccionados) {
    for (int i=0; i<p.predecesores.size(); i++) {
        int predecesor = p.predecesores[i];
        if (not seleccionados[predecesor]) {
            return false; //si no ha sido seleccionado retornamos falso
        }
    }

    return true;
}

void proyectosSeleccionados(vector<Proyecto>&proyectos,int n,int presupuesto) {
    sort(proyectos.begin(),proyectos.end(),compara);
    vector<bool> seleccionados(n+1,false);
    int costoTotal=0;
    int gananciaTotal=0;
    int puedeSeleccionar=true; //bandera que se usa para iterar de manera indefinida
    //indica si durante una iteración se pudo seleccionar un proyecto
    while (puedeSeleccionar) {
        puedeSeleccionar=false;
        for (int i=0 ; i<n ; i++) {
            //verificamos si el proyecto elegido ya fue seleccionado
            //esto para poder ignorarlo
            Proyecto p = proyectos[i];
            if (seleccionados[p.id]==true) {
                continue;
            }
            if (cumpleDependencias(p,seleccionados)) {
                if (costoTotal+p.costo<=presupuesto) {
                    seleccionados[p.id]=true; //guardamos como verdadero
                    //esto significa que el proyecto ha sido seleccionado
                    costoTotal+=p.costo;
                    gananciaTotal+=p.ganancia;
                    puedeSeleccionar=true;
                    cout<<"Proyecto seleccionado: "<<p.id<<endl;
                    break;
                }
            }
        }
    }


    // cout<<"Costo total: "<<costoTotal<<endl;
    cout<<"Ganancia total: "<<gananciaTotal<<endl;
}


int main() {
    int presupuesto=250;
    vector<Proyecto> proyectos(N);
    proyectos={
        {1,80,150,2,{}},
        {2,20,80,5,{4}},
        {3,100,300,1,{1,2}},
        {4,100,150,4,{}},
        {5,50,80,2,{}},
        {6,10,50,1,{2}},
        {7,50,120,2,{6}},
        {8,50,150,2,{6}},
    };
    int n = proyectos.size();
    proyectosSeleccionados(proyectos,n,presupuesto);

    return 0;
}
