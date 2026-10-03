#include <iostream>
#include <vector>
using namespace std;

#define RESTRICCION 50

struct Piso {
    vector<int> pacientes;
    int costo;
};

void buscarMejorCombinacion(vector<int>&pacientes,int idx,int acumulado,
        vector<int>&solu,int &mejorPeso,vector<int>&mejorSolucion) {
    //actualizar mejor solucion
    //actualizamos el peso
    //actualizamos la mejor solucion
    if (acumulado>mejorPeso) {
        mejorPeso=acumulado;
        mejorSolucion=solu;
    }

    for (int i=idx; i<pacientes.size(); i++) {
        if (acumulado+pacientes[i]>RESTRICCION) {
            continue; //si el acumulado supera la restriccion pasamos a la siguiente posicion
        }
        solu.push_back(i);
        buscarMejorCombinacion(pacientes,i+1,acumulado+pacientes[i],solu,
            mejorPeso,mejorSolucion);
        solu.pop_back();
    }

}


int main() {
    vector<Piso> pisos ={
        {{14,11,10,19,14,11},5},
        {{20,11,11,10,15,17,8},6},
        {{15,16,15,16},8},
        {{11,4,19,12,10},5},
        {{18,12},9}
    };
    vector<vector<int>> mejoresSoluciones(pisos.size());
    int kiloTotalLavado=0;
    int costoTotal=0;
    vector<int>kilosLavados(pisos.size());
    vector<int>costos(pisos.size());
    for (int i=0; i<pisos.size(); i++) {
        vector<int> solu;
        vector<int> mejorSolu;
        int mejorPeso=0;
        buscarMejorCombinacion(pisos[i].pacientes,0,0,solu,
            mejorPeso,mejorSolu);

        mejoresSoluciones[i]=mejorSolu;
        kilosLavados[i]=mejorPeso;
        costos[i]=mejorPeso*pisos[i].costo;

        int kilosTotalesPiso=0;
        for (int j=0; j<pisos[i].pacientes.size(); j++) {
            kilosTotalesPiso+=pisos[i].pacientes[j];
        }
    }

    cout<<"SOLUCION : "<<endl;
    for (int p=0 ; p<pisos.size(); p++) {
        cout<<"PISO "<< p+1<<endl;
        for (int i=0 ; i<mejoresSoluciones[p].size(); i++) {
            int paciente = mejoresSoluciones[p][i];
            cout<<"PACIENTE "<<paciente+1<<" = "<<pisos[p].pacientes[paciente] << " kg"<<endl;
        }
        
    }

    return 0;
}