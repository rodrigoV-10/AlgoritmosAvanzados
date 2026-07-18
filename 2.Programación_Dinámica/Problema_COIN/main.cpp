#include <iostream>

using namespace std;

#define N 6

//problema de la moneda
int main() {
    int coins[] = {0,5,1,2,10,6,2};
    int dp[N+1];
    //definimos caso base?
    dp[0] = 0;
    dp[1] = coins[1];
    //recorremos el array
    //pero desde i = 2 para evitar en posiciones negativas
    for (int i = 2; i <= N; i++) {
        //es decir coin[2] = 1
        // max ( 1+0 , 5) = 5
        //max (5+2, 5) = 7
        //max (10+5,7) = 15
        //max 
        dp[i] = max(dp[i-1] , dp[i-2]+ coins[i] );
    }

    cout << dp[N];

    return 0;
}
