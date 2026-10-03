#include <iostream>
#include <cmath>

using namespace std;

int mochila(int *pesos,int* valores,int n,int capacidad) {
    int dp[n+1][capacidad+1];
    //primera columna en 0
    for (int i=0 ; i<=n; i++) {
        dp[i][0] = 0;
    }
    //primera fila en 0
    for (int i=0 ; i<=capacidad; i++) {
        dp[0][i] = 0;
    }
    for (int i=1 ; i<=n ; i++) {
        for (int j=1 ; j<=capacidad ; j++) {
            int valor = valores[i-1];
            int peso = pesos[i-1];
            if (peso<=j) {
                //si cumple entonces podemos meterlo en la mochila y comparar si es factible meterlo o no
                dp[i][j]=max (  dp[i-1][j]      ,  valor + dp[i-1][j-peso]          );
            }else {
                //caso contrario solo copiamos el valor de la fila anterior de la matriz
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    // for (int i=0 ; i<=n ; i++) {
    //     for (int j=0 ; j<=capacidad ; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //
    // // cout<<dp[i-1][j]<<"  ----  "<<valor<<" + "<<dp[i-1][j-peso]<<endl ;
    return dp[n][capacidad];
}


int main() {
    int pesos[]={2,1,3,2};
    int n=sizeof(pesos)/sizeof(pesos[0]);
    int valor[] = {12,10,20,15};
    int peso=5;
    cout<<"Valor maximo: "<<mochila(pesos,valor,n,peso)<<endl;
    return 0;
}