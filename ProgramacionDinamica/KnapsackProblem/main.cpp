#include <iostream>
#include <iomanip>

using namespace std;

#define N 4

void dp_mochila(int *pesos,int *valores,int cant_pesos,int cant_valores,int W) {
    int dp[cant_pesos+1][W+1];
    //inicializamos filas
    for (int i=0; i<=cant_pesos; i++) {
        dp[i][0]=0;
    }

    //inicializamos las filas
    for (int i=0; i<=W; i++) {
        dp[0][i]=0;
    }

    for (int i=1;i<=cant_pesos;i++) {
        for (int j=1;j<=W;j++) {
            int valor = valores[i-1];
            int peso = pesos[i-1];
            if (j>=peso) {
                dp[i][j]=max(dp[i-1][j],valor+dp[i-1][j-peso]);
            }else {
                dp[i][j]=dp[i-1][j];
            }
        }
    }

    for (int i=0; i<=cant_valores; i++) {
        for (int j=0; j<=W; j++) {
            cout <<setw(3)<< dp[i][j] << " ";
        }
        cout << endl;
    }

}

int main() {
    int pesos[] = {2,1,3,2};
    int valores[]={12,10,20,15};
    int W=5;
    int cant_pesos = sizeof(pesos)/sizeof(pesos[0]);
    int cant_valores = sizeof(valores)/sizeof(valores[0]);
    dp_mochila(pesos,valores,cant_pesos,cant_valores,W);
    return 0;
}
