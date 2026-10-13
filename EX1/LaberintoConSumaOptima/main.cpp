#include <iostream>
#include <vector>
#define N 4
#define OBJETIVO 24
using namespace std;

bool esValido(int nx,int ny,vector<vector<int>>matriz,vector<vector<int>>visitado){
    return nx>=0 and ny>=0 and nx<N and ny<N and matriz[nx][ny]!=-1 and !visitado[nx][ny];
}

void generaCamino(int x,int y,int &acumulado,int movimientos[][2],
    vector<pair<int,int>>&caminoOptimo,vector<vector<int>>&matriz,
    vector<vector<int>>&visitado,vector<pair<int,int>>&ruta,int &acumuladoOptimo) {
    if (acumulado>OBJETIVO) {
        return;
    }

    //condicion de parada
    if (x==N-1 and y==N-1) {
        if (acumulado==OBJETIVO) {
            caminoOptimo=ruta;
            acumuladoOptimo = acumulado;
            return;
        }
    }
    for (int i=0; i<matriz.size() ; i++) {
        int nx = x+movimientos[i][0];
        int ny = y+movimientos[i][1];
        //validamos si se puede caminar
        if (esValido(nx,ny,matriz,visitado)) {
            //hago cambio
            ruta.push_back({nx,ny});
            acumulado+=matriz[nx][ny];
            visitado[nx][ny]=true;
            //backtrack
            generaCamino(nx,ny,acumulado,movimientos,caminoOptimo,matriz,visitado,ruta,acumuladoOptimo);
            //quito cambio
            acumulado-=matriz[nx][ny];
            visitado[nx][ny]=false;
            ruta.pop_back();
        }
    }

}


int main() {
    vector<vector<int>>matriz ={
        {2, 3,-1, 5},
        {4, 2, 3, 1},
        {1,-1, 4, 2},
        {6, 1, 2, 3}
    };
    int x=0, y=0;
    int acumulado = matriz[x][y];
    int acumuladoOptimo=0;
    //se trata de un void, don
    int movimientos[4][2]={
        {0,1},
        {-1,0},
        {0,-1},
        {1,0},
    };
    //se tratan de varias soluciones de las cuales tengo que buscar la que tiene menor costo
    vector<pair<int,int>>caminoOptimo;
    vector<pair<int,int>>ruta;
    vector<vector<int>>visitado(N,vector<int>(N,0));
    visitado[x][y]=true;
    caminoOptimo.push_back({x,y});
    generaCamino(x,y,acumulado,movimientos,caminoOptimo,matriz,visitado,ruta,acumuladoOptimo);
    vector<vector<int>>solucion(N,vector<int>(N,0));
    int cont=1;
    for (auto i : caminoOptimo) {
        solucion[i.first][i.second] = cont;
        cont++;
    }
    for (int i=0; i<solucion.size(); i++) {
        for (int j=0; j<solucion[i].size(); j++) {
            cout << solucion[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"Acumulado: "<<acumuladoOptimo<<endl;
    
    return 0;
}
