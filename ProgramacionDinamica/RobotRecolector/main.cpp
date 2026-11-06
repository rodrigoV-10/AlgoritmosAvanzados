#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int caminoRobot(vector<vector<int>>&matriz) {
    int n = matriz.size();
    int m = matriz[0].size();
    int dp[n][m];

    //primera celda
    dp[0][0] = matriz[0][0];
    //primera fila como no podemos movernos de arriba hacia abajo
    //nuestra suma es horizontal
    for (int i = 1; i < m; i++) {
        dp[0][i] = dp[0][i-1] + matriz[0][i];
    }

    //lo mismo ocurre con las filas, pues no puedo venir desde la derecha
    //al comienzo del problema
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][0] + matriz[i][0];
    }

    //para el resto de la matriz
    for (int i=1 ; i<n; i++) {
        for (int j=1; j<m; j++) {
            dp[i][j] = max(dp[i][j-1],dp[i-1][j]) + matriz[i][j];
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout << setw(3)<<dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp[n-1][m-1];
}


int main() {
    vector<vector<int>>matriz = {
        {1,3,1},
        {2,5,1},
        {4,2,1}
    };
    cout<<"Maximo: "<<endl<<caminoRobot(matriz)<<endl;
    return 0;
}
