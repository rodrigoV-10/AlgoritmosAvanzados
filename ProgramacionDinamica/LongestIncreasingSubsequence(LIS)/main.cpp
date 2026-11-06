#include <iostream>
#include <vector>

using namespace std;

#define N 8

int main() {
    int X[]={-7,10,9,2,3,8,8,1};
    int mejor=1;
    vector<int>dp(N,1);

    //con el fon para atras
    // for(int i=0;i<N;i++) {
    //     for(int j=0;j<i;j++) {
    //         //si donde estoy ahorita x[i] es mayor que donde estaba x[j]
    //         if (X[j]<X[i]) {
    //             //hago una comparacion de quien es mayor y si el dp[j]
    //             //es mayor le incremento en 1, que vendría a ser la longitud
    //             dp[i]=max(dp[i],dp[j]+1);
    //         }
    //     }
    //     mejor=max(mejor,dp[i]);
    // }

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if (X[j]>X[i]) {
                dp[i]=max(dp[i],dp[j]+1);
            }
        }
    }
    for (int i=0; i<dp.size(); i++) {
        mejor = max(mejor,dp[i]);
    }
    cout<<mejor<<endl;
    return 0;
}
