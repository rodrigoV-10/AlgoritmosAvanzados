#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

#define ITERACIONES 10000
#define ALFA 0.3
#define M 5 //lineas de produccion cada una con las 4 maquinas
#define N 20 //cantidad de ordenes

using namespace std;

struct Producto {
    int id;
    int cantidad;
    int prioridad;
};

struct LineaDeProduccion {
    vector<int>pedidos;
    int tiempo=0;
};

bool compara(Producto p1, Producto p2) {
    return p1.cantidad > p2.cantidad;
}

bool comparaConPrioridad(Producto p1, Producto p2) {
    if (p1.prioridad != p2.prioridad) {
        return p1.prioridad < p2.prioridad;
    }else {
        if (p1.prioridad==p2.prioridad) {
            return p1.cantidad > p2.cantidad;
        }
    }
}

int buscarRCL(vector<Producto>pedidos,double RCL) {
    int cantidad=0;
    for(int i=0;i<pedidos.size();i++) {
        if (pedidos[i].cantidad>=RCL) {
            cantidad++;
        }
    }
    return cantidad;
}

void graspA(vector<LineaDeProduccion>&lineasDeProduccion,vector<Producto>productos) {
    srand(time(NULL));
    int makespakn=INT_MAX;
    vector<LineaDeProduccion>mejorSolucion;
    for (int i=0;i<ITERACIONES;i++) {
        //criterio es empezar con los pedidos con mayor cantidad de botellas
        vector<Producto>pedidos;
        pedidos.insert(pedidos.begin(),productos.begin(),productos.end());
        sort(pedidos.begin(),pedidos.end(),compara);
        vector<LineaDeProduccion>unaSolucion(M);
        int mejorPos=0;
        while (!pedidos.empty()) {
            //construir RCL
            int beta = pedidos[0].cantidad;
            int tao  = pedidos[pedidos.size()-1].cantidad;
            double RCL = beta+ALFA*(tao-beta);
            int cantidad_rcl = buscarRCL(pedidos,RCL);
            if (cantidad_rcl==0) break;
            int indiceAleatorio = rand()%cantidad_rcl;

            //busco la linea con menor tiempo
            for (int j=0;j<M;j++) {
                if (unaSolucion[j].tiempo<unaSolucion[mejorPos].tiempo) {
                    mejorPos=j;
                }
            }
            //asingo el pedido a la linea con menor tiempo
            Producto unPedido;
            unPedido=pedidos[indiceAleatorio];
            unaSolucion[mejorPos].pedidos.push_back(unPedido.id);
            unaSolucion[mejorPos].tiempo += 6*unPedido.cantidad;
            pedidos.erase(pedidos.begin()+indiceAleatorio);
            sort(pedidos.begin(),pedidos.end(),compara);
        }
        int mayorTiempo=0;
        for (int j=0;j<M;j++) {
            if (unaSolucion[j].tiempo>mayorTiempo) {
                mayorTiempo=unaSolucion[j].tiempo;
            }
        }
        if (mayorTiempo<makespakn) {
            makespakn=mayorTiempo;
            mejorSolucion.clear();
            mejorSolucion=unaSolucion;
        }
    }
    cout<<"Primer Item: "<<endl;
    cout<<"Mejor Makespan: "<<makespakn<<endl;
    for (int i=0;i<mejorSolucion.size();i++) {
        cout<<"Linea "<<i+1<<": ";
        for (int j=0; j<mejorSolucion[i].pedidos.size();j++) {
            cout <<mejorSolucion[i].pedidos[j] << " ";
        }
        cout << endl;
    }
    cout<<endl;

}

void graspB(vector<LineaDeProduccion>&lineasDeProduccion,vector<Producto>productos) {
    srand(time(NULL));
    int makespakn=INT_MAX;
    vector<LineaDeProduccion>mejorSolucion;
    for (int i=0;i<ITERACIONES;i++) {
        //criterio es empezar con los pedidos con mayor cantidad de botellas
        vector<Producto>pedidos;
        pedidos.insert(pedidos.begin(),productos.begin(),productos.end());
        sort(pedidos.begin(),pedidos.end(),comparaConPrioridad);
        vector<LineaDeProduccion>unaSolucion(M);
        int mejorPos=0;
        while (!pedidos.empty()) {
            int prioridadActual=pedidos[0].prioridad;
            //contamos los pedidos con la misma prioridad
            int limite=0;
            while (limite<pedidos.size() and pedidos[limite].prioridad==prioridadActual) {
                //nuestro tope de acuerdo a la cantidad de
                //productos que hay con esa prioridad
                limite++;
            }

            //construir RCL dentro de esa misma prioridad
            int beta = pedidos[0].cantidad;
            int tao  = pedidos[pedidos.size()-1].cantidad;
            double RCL = beta+ALFA*(tao-beta);
            int cantidad_rcl=0;
            for (int k=0;k<limite;k++) {
                if (pedidos[k].cantidad>=RCL) {
                    cantidad_rcl++;
                }
            }
            int indiceAleatorio = rand()%cantidad_rcl;

            //busco la linea con menor tiempo
            for (int j=0;j<M;j++) {
                if (unaSolucion[j].tiempo<unaSolucion[mejorPos].tiempo) {
                    mejorPos=j;
                }
            }
            //asingo el pedido a la linea con menor tiempo
            Producto unPedido;
            unPedido=pedidos[indiceAleatorio];
            unaSolucion[mejorPos].pedidos.push_back(unPedido.id);
            unaSolucion[mejorPos].tiempo += 6*unPedido.cantidad;
            pedidos.erase(pedidos.begin()+indiceAleatorio);
            sort(pedidos.begin(),pedidos.end(),compara);
        }
        int mayorTiempo=0;
        for (int j=0;j<M;j++) {
            if (unaSolucion[j].tiempo>mayorTiempo) {
                mayorTiempo=unaSolucion[j].tiempo;
            }
        }
        if (mayorTiempo<makespakn) {
            makespakn=mayorTiempo;
            mejorSolucion.clear();
            mejorSolucion=unaSolucion;
        }
    }
    cout<<"Segundo item: "<<endl;
    cout<<"Mejor Makespan: "<<makespakn<<endl;
    for (int i=0;i<mejorSolucion.size();i++) {
        cout<<"Linea "<<i+1<<": ";
        for (int j=0; j<mejorSolucion[i].pedidos.size();j++) {
            cout <<mejorSolucion[i].pedidos[j] << " ";
        }
        cout << endl;
    }
    cout<<endl;

}

int main() {
    vector<Producto> productos(N);
    productos={
        {1 ,103,2},
        {2 ,58 ,1},
        {3 ,88 ,3},
        {4 ,126,1},
        {5 ,195,2},
        {6 ,90 ,2},
        {7 ,54 ,3},
        {8 ,195,1},
        {9 ,124,2},
        {10,113,3},
        {11,193,2},
        {12,55 ,1},
        {13,97 ,1},
        {14,97 ,2},
        {15,169,2},
        {16,50 ,2},
        {17,167,3},
        {18,74 ,1},
        {19,79 ,2},
        {20,109,1}
    };

    vector<LineaDeProduccion> lineasDeProduccion(M);
    graspA(lineasDeProduccion, productos);
    graspB(lineasDeProduccion, productos);


    return 0;
}
