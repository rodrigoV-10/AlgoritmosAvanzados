#include <iostream>

using namespace std;


int subconjunto(int *paquetes,int n,int peso) {
    //creamos la matriz
    //por teoria
    int dp[n+1][peso+1];
    //estamos formando conjuntos
    //siempre se puede formar conjunto del 0
    for (int i=0; i<=n ; i++) {
        dp[i][0]=1;
    }
    //y llenamos de 0 la primera fila pues con el
    //conjunto 0 no se puede formar ningun grupo
    for (int i=1; i<=peso ; i++) {
        dp[0][i]=0;
    }
    //recordar que la matriz es [paquete][suma]
    //y el llenado va a depende de los paquetes por eso la iterativa externa depende de los paquetes
    //recorremos nuestros "paquetes"
    for (int i=1; i<=n ; i++) {
        //y verificamos la cantidad de conjuntos que se pueden formar
        for (int j=1; j<=peso; j++) {
            //dp depende de una solución anterior
            //si el valor previamente existe o fue formado
            //entonces para futuras combinaciones si será posible formar ese valor
            //por eso asigno el valor previo [i-1][j] a la posicion actual [i][j]
            dp[i][j] = dp[i-1][j];

            if (j-paquetes[i-1]>=0 and dp[i][j]==0) {
                //formula para hallar el valor que se llena en la matriz
                dp[i][j]=dp[i-1][j-paquetes[i-1]];
            }
        }
    }
    for (int i=0 ; i<=n ; i++) {
        for (int j=0; j<=peso; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    return dp[n][peso];
}

int main() {
    //problema de los conjuntos
    //la suma de ambos subconjuntos es la misma :)
    //creamos un arreglo de los paquetes
    int paquetes[] = {1,3,4};
    int n = sizeof(paquetes)/sizeof(paquetes[0]);
    //cout<<n<<endl;
    //en este caso tienen que suar 10 :)
    cout<<subconjunto(paquetes,n,8)<<endl;

    return 0;
}
