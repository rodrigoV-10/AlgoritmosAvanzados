#include <iostream>
#include <vector>
using namespace std;


int rodCutting(vector<int>&precio,int n) {
    vector<int> dp(n+1,0);
    dp[0]=0;
    //longitud total
    for (int i = 1; i <= n; i++) {
        //longitud que estoy resolviendo
        for (int j=1; j<=i; j++) {
            int candidato = precio[j-1] + dp[i-j];
            dp[i] = max(dp[i],candidato);
        }
    }
    return dp[n];
}

int main() {
    vector<int> precio = {1,5,8,9};
    int n= 4;

    cout<<"Ganancia :"<<rodCutting(precio,n)<<endl;

    return 0;
}