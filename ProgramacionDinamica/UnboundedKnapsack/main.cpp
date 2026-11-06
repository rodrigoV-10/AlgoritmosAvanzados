#include <iostream>
#include <iomanip>
using namespace std;

int unboundedKnapsack(int *pesos,int *valores,int n,int W) {
    int dp[n+1][W+1];
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= W; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            int peso= pesos[i-1];
            int valor = valores[i-1];
            if (j >= peso) {
                dp[i][j]=max(dp[i][j-peso]+valor,dp[i-1][j]);
            }else {
                dp[i][j]=dp[i-1][j];
            }
        }
    }

    //impresion :
    for (int i=0 ; i<=n; i++) {
        for (int j=0 ; j<=W; j++) {
            cout <<setw(3)<< dp[i][j] << " ";
        }
        cout << endl;
    }
    cout<<"Valor maximo: "<<endl;
    return dp[n][W];
}



int main() {
    int pesos[] = {2,3,4};
    int valores[] = {4,5,7};

    int n = sizeof(pesos)/sizeof(pesos[0]);
    int W = 7;
    cout<<unboundedKnapsack(pesos,valores,n,W)<<endl;

    return 0;
}
