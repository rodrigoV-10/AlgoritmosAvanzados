#include <iostream>

using namespace std;

#define N 6

int main() {
    int moneda[]={0,5,1,2,10,6,2};
    int dp[N+1];
    //casos base
    dp[0]=moneda[0];
    dp[1]=moneda[1];
    for (int i=2; i<=N; i++) {
        dp[i] = max(dp[i-1],dp[i-2]+moneda[i]);
    }
    cout<<dp[N];
    return 0;
}
