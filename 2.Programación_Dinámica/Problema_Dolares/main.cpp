#include <iostream>
#include <climits>

using namespace std;

int maxcambio(int *precios,int n,int k) {
    int cambio[k+1][n];
    int maximo;
    for (int i = 0; i <= k; i++)  cambio[i][0] = 0;
    for (int i = 0; i < n; i++)  cambio[0][i] = 0;

    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < n; j++) {
            maximo = INT_MIN;
            for (int m=0;m<j;m++)
                if (m==0)
                    maximo=max(maximo,precios[j]-precios[m]);
                else
                    maximo=max(maximo,precios[j]-precios[m]+cambio[i-1][m-1]);
            cambio[i][j] =max(maximo,cambio[i][j-1]);
        }
    }
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < n; j++)
            cout << cambio[i][j] << " ";
        cout << endl;
    }


    return cambio[k][n-1];
}

int main() {
    int k=3;
    int precios[]={315,320,330,350,370,340,390};
    int n=sizeof(precios)/sizeof(precios[0]);
    cout << maxcambio(precios,n,k) << endl;

    return 0;
}

