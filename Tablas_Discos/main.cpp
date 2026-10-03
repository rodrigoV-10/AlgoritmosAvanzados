#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Objeto {
    int id;
    int velocidad;
};

//se desea realizar una optimización
//centrandose en la asignacion de tablas con demanda de MAYOR VELOCIDAD
//EN LOS DISCOS DE MAYOR VELOCIDAD
bool compara(Objeto a, Objeto b) {
    return a.velocidad>b.velocidad;
}


void discosDeHuaman(vector<Objeto>&Tablas,vector<Objeto>&Disco,int n,int m) {
    //ordenamos los discos de mayor a menor al igual que las tablas
    sort(Tablas.begin(),Tablas.end(),compara);
    sort(Disco.begin(),Disco.end(),compara);
    //yo asigno tablas a los discos
    //una asigne actualizo la velocidad a ese disco
    //si ese disco ya no se puede actualizar lo borro entonces y paso al siguiente
    vector<vector<int>> solucion(m+1);
    for (int i=0;i<n;i++) {
        int velocidad = Tablas[i].velocidad;
        int idTabla = Tablas[i].id;
        for (int j=0;j<m;j++) {
            if (Disco[j].velocidad>=velocidad) {
                int idDisco = Disco[j].id;
                //asignamos la tabla al disco
                solucion[idDisco].push_back(idTabla);
                Disco[j].velocidad -= velocidad;
                //ordenamos la velocidad porque este disco acaba de cambiar
                sort(Disco.begin(),Disco.end(),compara);
                break;
            }

        }
    }
    cout<<"Disco "<<" Tablas"<<endl;
    for (int i = 1 ; i<solucion.size();i++) {
        cout<<"   "<<i<<"     ";
        for (int j=0;j<solucion[i].size();j++) {
            cout << solucion[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    vector<Objeto> Tablas = {
        {1,150},
        {2,100},
        {3,180},
        {4,50},
        {5,120},
        {6,10},
    };

    vector<Objeto> Disco ={
        {1,250},
        {2,200},
        {3,200},
        {4,100},
    };

    int n = Tablas.size();
    int m = Disco.size();

    discosDeHuaman(Tablas, Disco, n, m);

    return 0;
}
