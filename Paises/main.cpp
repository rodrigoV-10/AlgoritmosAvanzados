#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define ARGENTINA 1
#define BOLIVIA 2
#define BRASIL 3
#define CHILE 4
#define COLOMBIA 5
#define ECUADOR 6
#define GUYANA 7
#define PARAGUAY 8
#define PERU 9
#define SURINAM 10
#define URUGUAY 11
#define VENEZUELA 12

#define MAX 12

using namespace std;

struct Pais {
    int id;
    vector<int> vecinos;
};

//Se pide colorear el mapa con la menor cantidad de colores posibles
//con la condicion de que paises limitrofes no tengan el mismo color
bool compara(Pais p1, Pais p2) {
    if (p1.vecinos.size() != p2.vecinos.size())
        return p1.vecinos.size() > p2.vecinos.size();
    else
        return p1.id>p2.id;
}


int colorear(vector<Pais>&paises,int matriz[MAX][MAX],vector<int>&colores) {
    sort(paises.begin(),paises.end(),compara);
    int maxColor=INT_MIN;
    for(int i=0;i<paises.size();i++) {
        int actual = paises[i].id-1;
        //usados[color] indica si un vecino ya esta utilizando ese color
        vector<bool>usados(MAX+1,false);
        //revisamos los vecinos del pais actual
        for (int j=0; j<MAX ; j++) {
            //si es vecino
            //si ese vecino ya fue coloreado
            if (matriz[actual][j]==1 && colores[j]!=0) {
                usados[colores[j]]=true;
            }
        }
        int color = 1;
        while (usados[color]) {
            color++;
        }
        //coloreamos el pais
        colores[actual]=color;

        if (color>maxColor) {
            maxColor=color;
        }
    }
    return maxColor;
}

int main() {
    vector<Pais> paises = {
        {ARGENTINA,{CHILE,BOLIVIA,PARAGUAY,BRASIL,URUGUAY}},
        {BOLIVIA,{PERU,BRASIL,PARAGUAY,ARGENTINA,CHILE}},
        {BRASIL,{URUGUAY,ARGENTINA,PARAGUAY,BOLIVIA,PERU,COLOMBIA,VENEZUELA,GUYANA,SURINAM}},
        {CHILE,{PERU,BOLIVIA,ARGENTINA}},
        {COLOMBIA,{VENEZUELA,BRASIL,PERU,ECUADOR}},
        {ECUADOR,{COLOMBIA,PERU}},
        {GUYANA,{VENEZUELA,BRASIL,SURINAM}},
        {PARAGUAY,{BOLIVIA,BRASIL,ARGENTINA}},
        {PERU,{ECUADOR,COLOMBIA,BRASIL,BOLIVIA,CHILE}},
        {SURINAM,{GUYANA,BRASIL}},
        {URUGUAY,{BRASIL,ARGENTINA}},
        {VENEZUELA,{COLOMBIA,BRASIL,GUYANA}}
    };

    int matriz[MAX][MAX];
    for(int i=0;i<MAX;i++) {
        for(int j=0;j<MAX;j++) {
            matriz[i][j]=0;
        }
    }
    //recorremos cada pais
    for (int i=0 ; i<paises.size(); i++) {
        int origen = paises[i].id-1;
        //recorremos los vecinos
        for (int j=0 ; j<paises[i].vecinos.size(); j++) {
            int destino = paises[i].vecinos[j]-1;
            matriz[origen][destino] = 1;
            matriz[destino][origen] = 1;
        }
    }
    //guardamos el color de cada pais
    vector<int> colores(MAX,0);
    int cantidadColores = colorear(paises,matriz,colores);
    cout<<"Cantidad de colores: "<<cantidadColores<<endl;

    vector<string> nombres = {
        "Argentina",
        "Bolivia",
        "Brasil",
        "Chile",
        "Colombia",
        "Ecuador",
        "Guyana",
        "Paraguay",
        "Peru",
        "Surinam",
        "Uruguay",
        "Venezuela"
    };
    //mostramos los paises agrupados por color
    for (int color=1; color<=cantidadColores; color++) {
        cout<<"Color "<<color<<":"<<endl;
        for (int i=0; i<MAX; i++) {
            if (colores[i]==color) {
                cout<<nombres[i]<<" ";
            }
        }
        cout<<endl;
    }

    return 0;
}
