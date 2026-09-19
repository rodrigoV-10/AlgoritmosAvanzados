#include <iostream>
#include <iomanip>

using namespace std;


int banderas(int n) {
    int dp[n+1][2];
    //columna en 0 : termina en no rojo
    //columna en 1 : termina en rojo
    //dp[i][0 o 1]
    dp[1][0]=2;  //azul o blanco
    dp[1][1]=1; //rojo

    for (int i=2 ; i<=n; i++) {
        //terminar en rojo
        //anteriormente no podía terminar en rojo
        dp[i][1]= dp[i-1][0];
        //terminar en azul o blanco
        dp[i][0] = 2*(dp[i-1][0]+dp[i-1][1]);
    }
    cout << "i   NoRojo   Rojo" << endl;

    for (int i = 1; i <= n; i++) {

        cout << setw(2) << i
             << setw(9) << dp[i][0]
             << setw(7) << dp[i][1]
             << endl;
    }

    return dp[n][0]+dp[n][1];
}



int main() {
    int n = 3;
    cout<<"Cantidad de banderas: "<<endl<<banderas(n)<<endl;
    return 0;
}