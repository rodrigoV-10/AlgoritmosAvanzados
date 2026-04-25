#include <iostream>

using namespace std;

long long fibonacci(long long N) {
    if (N<=1)return N;
    return fibonacci(N-1)+fibonacci(N-2);
}

int main() {
    long long N = 40;
    //ponemos un tope a nuestra sucesión de fibonacci
    //creamos el arreglo
    long long dp[N+1];
    //definimos casos base :) <- para ciertos problemas existen casos base
    dp[0] = 0;
    dp[1] = 1;
    for (int i=2 ; i<=N ; i++) {
        //empezamos de 2 porque
        //recién sumamos en el 2do dos y en el arreglos es arr[i=2] es decir pos = 3
        // 0 , 1 , 1 (inicia la sucesion) , 2
        dp[i] = dp[i-1]+dp[i-2];
    }
    //calculando por DP
    cout<<"Fibonacci N DP: "<<dp[N]<<endl;
    //calculando por recursividad
    cout<<"Fibonacci N RECURSIVE: "<<fibonacci(N)<<endl;
    return 0;
}
