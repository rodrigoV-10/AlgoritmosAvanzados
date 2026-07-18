#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


//minimizar el número de cortes

struct Pedido {
    int tamano;
    int cantidad;
};

bool compara(Pedido p1, Pedido p2) {
    return p1.tamano > p2.tamano;
}

void procesarPedidos(vector<int> &barras,vector<Pedido> pedidos,int &cantidad_barra) {
    //recorremos los pedidos que tenemos :)
    for (int i=0; i<pedidos.size(); i++) {
        //cada pedido tiene una cantidad solicitadas
        for (int j=0; j<pedidos[i].cantidad; j++) {
            //ahora veremos que cantidad entra de acuerdo a nuestra longitud de barra
            //que tenemos disponible -> Longitud = 10
            for (int k=0; k<barras.size(); k++) {
                //si la barra es mayor al tamaño solicitad
                if (barras[k]>=pedidos[i].tamano) {
                    //actualizamos el valor de la barra
                    barras[k] = barras[k] - pedidos[i].tamano;
                    break; //ya se colocó entonces pasamos a la siguiente barra
                }
            }
        }
    }
    //para calcular  la merma
    int merma=0;
    for (int i=0 ; i<barras.size(); i++) {
        if (barras[i]<10) {
            cantidad_barra++;
            merma = merma + barras[i];
        }
    }
    cout<<"La merma total: "<<merma<<endl;
}

void ingresarPedidos(vector<Pedido> &pedidos) {
    vector<int> cantidad_pedida = {6 , 3, 4, 7, 3};
    vector<int> longitud =        {6 , 5, 3, 2 ,1};
    for (int i = 0; i < cantidad_pedida.size(); i++) {
        Pedido ped ;
        ped.cantidad = cantidad_pedida[i];
        ped.tamano = longitud[i];
        pedidos.push_back(ped);
    }
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    vector<Pedido> pedidos;
    ingresarPedidos(pedidos);
    // for (int i = 0; i < pedidos.size(); i++) {
    //     cout<<pedidos[i].tamano<<"   ";
    //     cout<<pedidos[i].cantidad<<endl;
    // }
    sort(pedidos.begin(), pedidos.end(),compara);
    // for (int i = 0; i < pedidos.size(); i++) {
    //     cout<<pedidos[i].tamano<<"   ";
    //     cout<<pedidos[i].cantidad<<endl;
    // }
    vector<int>barras(100,10);
    //se lee como un arreglo de 100 barras con longitud 10
    int cantidad_barra=0;
    procesarPedidos(barras,pedidos,cantidad_barra);
    cout<<"La cantidad de barras utilizadas : "<<cantidad_barra<<endl;

    return 0;
}