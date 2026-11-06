#include <iostream>
#include <vector>

#define N 4

using namespace std;

bool hamiltoniano(int grafo[N][N],vector<int>&camino,vector<bool>&visitado) {
    if (camino.size()==N) {
        int ultimo = camino.back();
        int primero = camino[0];
        if (grafo[ultimo][primero]==1) {
            camino.push_back(primero);
            return true;
        }
        return false;
    }
    int actual = camino.back();
    for (int i=0; i<N; i++) {
        if (grafo[actual][i]!=0 and !visitado[i]) {
            camino.push_back(i);
            visitado[i] = true;

            if (hamiltoniano(grafo,camino,visitado)) {
                return true;
            }

            camino.pop_back();
            visitado[i] = false;
        }
    }
    return false;
}


int main() {
    int grafo[N][N]={
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0}
    };

    vector<int> camino;
    vector<bool> visitado(N, false);

    //punto de partinda
    camino.push_back(0);
    visitado[0] = true;
    if (hamiltoniano(grafo,camino,visitado)) {
        for (auto v : camino) {
            cout << v << " ";
        }
    }

    return 0;
}
