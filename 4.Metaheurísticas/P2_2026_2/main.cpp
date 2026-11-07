#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>
#define ITERACIONES 1000
#define ALFA 0.2
#define PESO_MAX 50
using namespace std;

struct Pedido{
    char letra;
    int peso;
};

struct Camion {
    int peso=0;
    vector<Pedido> pedidos;
};

bool compara(Pedido p1, Pedido p2) {
    return p1.peso > p2.peso;
}

int calcularRCL(vector<Pedido>listaDePedidos,double RCL) {
    int cont=0;
    for (int i=0;i<listaDePedidos.size();i++) {
        if (listaDePedidos[i].peso>=RCL) {
            cont++;
        }
    }
    return cont;
}


void graspCamionesCoscu(vector<Pedido>&pedidos,vector<Camion>&camiones) {
    srand(time(NULL));
    vector<Camion> mejorSolucion;
    int mejor=INT_MAX;
    for(int i=0;i<ITERACIONES;i++) {
        vector<Camion> listaCamiones;
        vector<Pedido> listaDePedidos = pedidos;
        sort(listaDePedidos.begin(),listaDePedidos.end(),compara);
        while (!listaDePedidos.empty()) {
            int beta = listaDePedidos[0].peso;
            int tao = listaDePedidos[listaDePedidos.size()-1].peso;
            double RCL = beta+ALFA*(tao-beta);
            int umbral = calcularRCL(listaDePedidos,RCL);
            if (umbral==0) break;
            int indiceAleatorio = rand()%umbral;

            Pedido pedSeleccionado = listaDePedidos[indiceAleatorio];
            bool pedidoColoado=false;
            //el vector me genera un camion por default entonces recorro el camion que tengo
            for (int c = 0 ; c<listaCamiones.size();c++) {
                if (listaCamiones[c].peso+pedSeleccionado.peso<=PESO_MAX) {
                    listaCamiones[c].peso+=pedSeleccionado.peso;
                    listaCamiones[c].pedidos.push_back(pedSeleccionado);
                    pedidoColoado=true;
                    break;
                }
            }
            if (not pedidoColoado) {
                Camion nuevo;
                nuevo.peso+=pedSeleccionado.peso;
                nuevo.pedidos.push_back(pedSeleccionado);
                listaCamiones.push_back(nuevo);
            }
            listaDePedidos.erase(listaDePedidos.begin()+indiceAleatorio);
        }
        if (listaCamiones.size()<mejor) {
            mejor=listaCamiones.size();
            mejorSolucion.clear();
            mejorSolucion = listaCamiones;
        }
    }

    camiones = mejorSolucion;

    cout << "===== MEJOR SOLUCION GRASP =====" << endl;

    for (int i=0; i<camiones.size(); i++) {

        cout << "Camion " << i+1 << ": ";

        for (int j=0; j<camiones[i].pedidos.size(); j++) {
            cout << camiones[i].pedidos[j].letra << " ";
        }

        cout << "| Peso: " << camiones[i].peso
             << "/" << PESO_MAX << " kg" << endl;
    }

    cout << "Cantidad total de camiones: "
         << mejor << endl;

}


int main() {
    vector<Pedido> pedidos={
        {'A',15},
        {'B',32},
        {'C',20},
        {'D',42},
        {'E',8},
        {'F',18},
    };
    vector<Camion> camiones;

    graspCamionesCoscu(pedidos, camiones);

    return 0;
}
