#include <iostream>
#include <vector>

#define N 5

using namespace std;

bool esValido(int nx,int ny,vector<vector<int>>matriz,vector<vector<int>>visitados) {
    return nx>=0 && ny>=0 && nx<N and ny<N && matriz[nx][ny]!=0 and visitados[nx][ny]==0;
}

void backtracFRACA(int x,int y,int &mejorCosto,vector<vector<int>>matriz,
    int movimientos[][2],vector<vector<int>>&visitados,
    vector<pair<int,int>>&ruta,vector<pair<int,int>>&mejorRuta,int valorAcumulado) {
    if (valorAcumulado>=mejorCosto) {
        //cout<<"Camino descartado: "<<valorAcumulado<<endl;
        return;
    }

    if (x==N-1 && y==N-1) {
        mejorCosto = valorAcumulado;
        mejorRuta = ruta;
        return;
    }

    for (int i=0;i<N-1;i++) {
        int nx = x + movimientos[i][0];
        int ny = y + movimientos[i][1];
        if (esValido(nx,ny,matriz,visitados)) {
            int valor = matriz[nx][ny];
            visitados[nx][ny]=1;
            ruta.push_back({nx,ny});
            backtracFRACA(nx,ny,mejorCosto,matriz,
                movimientos,visitados,ruta,mejorRuta,valorAcumulado+valor);

            ruta.pop_back();
            visitados[nx][ny]=0;
        }
    }

}


int main() {

    vector<vector<int>> matriz={
        {1,2,0,1,0},
        {3,2,3,1,1},
        {0,1,2,0,0},
        {3,1,1,2,3},
        {0,1,3,1,1}
    };

    vector<vector<int>>visitados={
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    vector<pair<int,int>>ruta;
    vector<pair<int,int>>mejorRuta;

    int movimientos[4][2]={
        {0,1},
        {1,0},
        {0,-1},
        {-1,0},
    };
    int mejorCosto = INT_MAX;
    visitados[0][0]=1;
    ruta.push_back({0,0});
    int valorAcumulado=matriz[0][0];
    backtracFRACA(0,0,mejorCosto,matriz,movimientos,
        visitados,ruta,mejorRuta,valorAcumulado);
    vector<vector<int>> solucion(N,vector<int>(N,0));
    for (auto i : mejorRuta) {
        solucion[i.first][i.second]=1;
    }
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            cout << solucion[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"Costo minimo: "<<mejorCosto<<endl;

    return 0;
}
