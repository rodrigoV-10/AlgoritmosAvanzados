#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Orden {
    int id;
    char tipo;
    int peso;
};

struct Lavadora {
    int id;
    int tiempo;
    vector<int> ordenes;
};

void asignarLavaTUPIA(vector<Orden>&ordenes,int n,
    vector<Lavadora>&lavadoras,int peso) {
    //recorremos todas las ordenes
    for (int i=0;i<ordenes.size();i++) {
        Orden actual = ordenes[i];
        int tiempo; //calculamos el tiempo de la orden
        if (actual.tipo=='L') {
            tiempo = actual.peso*4;
        }else {
            tiempo = actual.peso*2;
        }
        //en este tipo de problemas de asignacion siempre se asigna el primer objeto
        int posMenor = 0;
        //a cada lavadora se le asigna una orden
        for (int j = 1 ; j<lavadoras.size(); j++) {
            if (lavadoras[j].tiempo < lavadoras[posMenor].tiempo) {
                posMenor = j;
            }
        }
        //asignamso la orden a una lavadora
        lavadoras[posMenor].ordenes.push_back(actual.id);
        //actualizamos el tiempo de la lavadora
        lavadoras[posMenor].tiempo+=tiempo;

    }
}

int main() {
    //una orden de trabajo son 2 acciones lavar o secar ropa
    //cada orden tiene un peso
    //nunca se supera los 15 kg
    //cada 5 kilos de ropa demora 20 min en ser lavado y 10 en ser secado
    //20 ordenes y 5 lavadoras
    vector<Orden> ordenes= {
        {1,'L',10},
        {2,'L',10},
        {3,'S',8},
        {4,'L',15},
        {5,'S',9},
        {6,'S',11},
        {7,'L',12},
        {8,'S',15},
        {9,'L',6},
        {10,'S',10},
        {11,'L',8},
        {12,'S',15},
        {13,'L',11},
        {14,'L',7},
        {15,'L',7},
        {16,'S',8},
        {17,'S',9},
        {18,'L',11},
        {19,'S',12},
        {20,'L',15},
    };
    int n = ordenes.size();
    int peso = 15;
    vector<Lavadora> lavadoras = {
        {1,0,{}},
        {2,0,{}},
        {3,0,{}},
        {4,0,{}},
        {5,0,{}},
    };

    asignarLavaTUPIA(ordenes,n, lavadoras,peso);

    for (int i=0; i<lavadoras.size(); i++) {
        cout<<"Lavadora "<<lavadoras[i].id<<" : ";
        for (int j=0; j<lavadoras[i].ordenes.size(); j++) {
            cout<<" "<<lavadoras[i].ordenes[j];
        }
        cout<<endl;
        cout<<"Tiempo total: "<<lavadoras[i].tiempo<<" min"<<endl;
    }

    return 0;
}
