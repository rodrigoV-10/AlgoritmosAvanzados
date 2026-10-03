#include <iomanip>
#include <iostream>

using namespace std;

void ordenarmiento(int* inicio,int* fin,int* beneficio,int n) {
    //ordenamiento burbuja
    for (int i=0 ; i<n-1 ; i++) {
        for (int j=0; j<n-i-1 ; j++) {
            if (fin[j]>fin[j+1]) {
                swap(inicio[j],inicio[j+1]);
                swap(fin[j],fin[j+1]);
                swap(beneficio[j],beneficio[j+1]);
            }
        }
    }
}

/*
 * Buscamos hacia atrás la última presentación cuyo fin sea <= al inicio
 * de la presentación actual
 */
int esValido(int inicio[],int fin[],int actual) {
    for (int i=actual-1 ; i>=0 ; i--) {
        if (fin[i]<=inicio[actual]) {
            return i;
        }
    }
    return -1;
}

int cortesDeMadera(int *inicio,int *fin,int *beneficio,int n,int M) {
    int dp[M+1];
    for (int i=0 ; i<M ; i++) {
        dp[i]=0;
    }
    dp[0]=0;
    for (int i=1; i<=M ; i++) {
        int actual = i-1;
        int posValida=esValido(inicio,fin,actual);
        int tomar;
        int noTomar= dp[i-1];
        if (posValida!=-1) {
            tomar = beneficio[actual] + dp[posValida+1];
        }else {
            tomar = beneficio[actual];
        }
        dp[i] = max(tomar,noTomar);
    }
    for (int i=0; i<=M ; i++) {
        cout<<setw(5)<<dp[i];
    }
    cout<<endl;
    return dp[M]*10;
}


int main() {
    int inicio[] = {5 , 2 , 6 , 4};
    int fin[] = {10 , 4 , 12 , 15};
    int beneficio[]={30, 40 , 80 , 100};
    int n= sizeof(beneficio)/sizeof(beneficio[0]);
    int N = 10; // cantidad de troncos
    int M = 4; // cantidad de presentaciones
    //ordenamos para que no se solapen
    ordenarmiento(inicio,fin,beneficio,n);
    cout<<cortesDeMadera(inicio,fin,beneficio,n,M);
    return 0;
}