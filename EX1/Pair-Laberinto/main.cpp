#include <iostream>
#include <vector>

#define N 4

using namespace std;

bool esValido(int nx,int ny,
    vector<vector<int>>laberinto,vector<vector<int>>visitados,
    vector<pair<int,int>>camino) {
    return nx>=0 && ny>=0 && nx<N && ny<N and laberinto[nx][ny]!=1
    and visitados[nx][ny]==0;
}

bool backTracking(int x,int y,vector<vector<int>>laberinto
    ,vector<vector<int>>&visitados,vector<pair<int,int>>&camino) {
    if (x==N-1 && y==N-1) {
        return true;
    }
    int movimientos[4][2]={
        {-1,0},
        {1,0},
        {0,1},
        {0,-1},
    };

    for (int i = 0; i < N; i++) {
        int nx=x+movimientos[i][0];
        int ny=y+movimientos[i][1];
        if (esValido(nx,ny,laberinto,visitados,camino)) {

            camino.push_back({nx,ny});
            visitados[nx][ny]=1;

            if (backTracking(nx,ny,laberinto,visitados,camino)) {
                return true;
            }

            camino.pop_back();
            visitados[nx][ny]=0;
        }
    }
    return false;
}


int main() {
    //1 es obstaculo
    //0 camino libre
    vector<vector<int>>laberinto = {
        {0,0,1,0},
        {1,0,1,0},
        {0,0,0,0},
        {0,1,1,0}
    };

    vector<vector<int>> visitados(N, vector<int>(N, 0));
    vector<pair<int,int>> camino;
    camino.push_back({0,0});
    visitados[0][0]=1;
    if (backTracking(0,0,laberinto,visitados,camino)) {
        cout<<"COORDENADAS"<<endl;
        for (int i = 0; i < camino.size(); i++) {

            cout<<"("<<camino[i].first<<","<<camino[i].second<<")"<<endl;
        }
        cout<<"CAMINO DE LA MATRIZ"<<endl;
        for (int i=0; i<visitados.size(); i++) {
            for (int j=0; j<visitados[i].size(); j++) {
                cout<<visitados[i][j]<<" ";
            }
            cout<<endl;
        }


    }

    return 0;
}
