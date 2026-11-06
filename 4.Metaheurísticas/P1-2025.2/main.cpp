#include <iostream>
#include <vector>
#include <climits>
#include <random>
#include <algorithm>

#define ITERACIONES 10000
#define ALFA 0.15

using namespace std;

struct Objeto {
    char id;
    int ancho;
    int alto;
    int area=0;
};

struct Fila {
    int anchoUsado=0;
    int alto=0;
    vector<Objeto> objetos;
};

struct Estante {
    int ancho=10;
    int alto=10;
    int area=alto*ancho;
    //vector<Objeto> objetos;
    vector<Fila> filas;
    int altoUsado=0;
};

//queremos meter todos los objetos
bool compara(Objeto a,Objeto b) {
    return a.area>b.area;
}

bool colocar(Estante &unEstante,Objeto objeto) {
    //si no cabe creo que la primera validación esta demás
    if (objeto.ancho>10 || objeto.alto>10 ||
        objeto.ancho<=0 || objeto.alto<=0) {
        return false;
    }
    //buscamos una fila en ese estante
    for (int i=0; i<unEstante.filas.size();i++) {
        if (unEstante.filas[i].anchoUsado+objeto.ancho<=10 and
            objeto.alto<=unEstante.filas[i].alto) {
            unEstante.filas[i].anchoUsado+=objeto.ancho;
            unEstante.filas[i].objetos.push_back(objeto);
            return true;
        }
    }

    if (unEstante.altoUsado+objeto.alto<=10) {
        Fila nueva;
        nueva.anchoUsado+=objeto.ancho;
        nueva.alto+=objeto.alto;
        nueva.objetos.push_back(objeto);
        unEstante.filas.push_back(nueva);
        unEstante.altoUsado+=objeto.alto;
        return true;
    }

    return false;

}


int buscarRCL(double RCL,vector<Objeto>vObjetos) {
    int cantidad=0;
    for (int i=0;i<vObjetos.size();i++) {
        if (vObjetos[i].area>=RCL) {
            cantidad++;
        }
    }
    return cantidad;
}

//queremos minimizar la cantidad de contenedores
//entonces tenemos que meter la mayor cantidad de objetos posibles
void grasp(vector<Objeto>&objetos,vector<Estante>&estantes) {
    srand(time(NULL));
    int mejor=INT_MAX;
    vector<Estante> mejorSolucion;
    for (int i=0;i<ITERACIONES;i++) {
        vector<Estante>unaSolucion;
        vector<Objeto> vObjetos;
        vObjetos.insert(vObjetos.begin(),objetos.begin(),objetos.end());
        sort(vObjetos.begin(),vObjetos.end(),compara);
        while (!vObjetos.empty()) {

            int beta=vObjetos[0].area;
            int tao=vObjetos[vObjetos.size()-1].area;
            double RCL = beta-ALFA*(beta-tao);
            int cantidad_RCL = buscarRCL(RCL,vObjetos);
            int indiceAleatorio= rand() % cantidad_RCL;
            Objeto objetoAleatorio = vObjetos[indiceAleatorio];

            bool objetoAsignado=false;
            //recorremos los estantes actuales
            //el vector nos asigna como taño 1 por default
            for (int c = 0 ; c<unaSolucion.size();c++) {
                if (colocar(unaSolucion[c],objetoAleatorio)) {
                    objetoAsignado=true;
                    break;
                }
            }

            if (not objetoAsignado) {
                //si no fue asignado creamos un nuevo estante
                Estante nuevo;
                if (colocar(nuevo,objetoAleatorio)) {
                    unaSolucion.push_back(nuevo);
                }else {
                    return;
                }
            }
            vObjetos.erase(vObjetos.begin()+indiceAleatorio);
        }
        if (unaSolucion.size()<mejor) {
            mejor=unaSolucion.size();
            mejorSolucion.clear();
            mejorSolucion=unaSolucion;
        }
    }

    for (int i=0; i<mejorSolucion.size();i++) {
        cout<<"Estante "<<i+1<<endl;
        for (int j=0;j<mejorSolucion[i].filas.size();j++) {
            cout<<"Fila "<<j+1<<": ";
            for (int k=0;k<mejorSolucion[i].filas[j].objetos.size();k++) {
                cout<<mejorSolucion[i].filas[j].objetos[k].id<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

}


int main() {
    vector<Objeto> objetos;
    objetos={
        {'A',6,5},
        {'B',4,5},
        {'C',3,3},
        {'D',5,5},
        {'E',2,2}
    };

    for (int i=0;i<objetos.size();i++) {
        objetos[i].area=objetos[i].alto*objetos[i].ancho;
    }
    vector<Estante> estantes;
    grasp(objetos,estantes);

    return 0;
}
