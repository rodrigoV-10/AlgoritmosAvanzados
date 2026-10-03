#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

int partition(int particion,int  *numeros,int  n) {
    int dp[n+1][particion+1];
    //formar la suma 0 es posible
    for(int i=0; i<=n; i++) {
        dp[i][0] = 1;
    }
    //no podemos guardar en una mochila de 0 capacidad valores >0
    for(int i=1; i<=particion; i++) {
        dp[0][i] = 0;
    }

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=particion; j++) {
            int valor = numeros[i-1];
            if (j>=valor) {
                //tomar o o no tomar
                //si con lo que tenía puedo formar j   " o "
                //con puedo formar este nuevo valor tomadolo
                dp[i][j] = dp[i-1][j] || dp[i-1][j-valor];
            }else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    for (int i=0; i<=n; i++) {
        for (int j=0; j<=particion; j++) {
            cout << setw(3)<< dp[i][j] << " ";
        }
        cout << endl;
    }
    cout<<dp[n][particion]<<endl;
    return dp[n][particion];
}


int main() {
    int numeros[] = {1,5,11,5};
    int n = sizeof(numeros)/sizeof(numeros[0]);
    int suma = 0;
    for(int i = 0; i < n; i++) {
        suma = suma + numeros[i];
    }
    int particion = suma / 2;
    if (partition(particion, numeros, n)) {
        cout<<"Se puede formar el valor "<<endl;
    }else {
        cout<<"No se puede formar el valor "<<endl;
    }
    return 0;
}
