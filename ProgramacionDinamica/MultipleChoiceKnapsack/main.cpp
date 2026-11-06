#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Equipo {
    int costo;
    int beneficio;
};

int multipleChoiceKnapsack(vector<vector<Equipo>>&equipos,int  n,int W) {
    int dp[n+1][W+1];

    //con 0 grupos beneficio 0 para cualquier capacidad
    for (int i=0;i<=W;i++) {
        dp[0][i] = 0;
    }

    //con grupos >0 y capacidad 0
    //imposible de elegir exactamente 1
    for (int i=1;i<=n;i++) {
        dp[i][0] = -1;
    }

    //recorremos los grupos
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=W;j++) {
            //recorremos la opción de cada grupo
            //inicialmente este estado es imposible
            dp[i][j]=-1; //asumimos que no hay opción valida
            //no se ha encontrado una solucion valida para esa celda
            for (int k=0; k<equipos[i-1].size(); k++) {
                int costo = equipos[i-1][k].costo;
                int beneficio = equipos[i-1][k].beneficio;
                if (j>=costo) {
                    if (dp[i-1][j-costo] != -1) {  //evita que tomemos una solución invalida :)
                        int candidato = beneficio + dp[i-1][j-costo];
                        dp[i][j] = max(dp[i][j], candidato);
                    }

                }

            }

        }
    }

    for (int i=0;i<=n;i++) {
        for (int j=0;j<=W;j++) {
            cout<<setw(3)<<dp[i][j]<<" ";
        }
        cout<<endl;
    }

    return dp[n][W];

}



int main() {

    vector<vector<Equipo>> equipos = {
        //grupo 1
        {{3,8},{5,12},{6,14}},
        //grupo 2
        {{2,5},{4,9},{5,11}},
        //grupo 3
        {{1,3},{3,7},{4,10}}
    };
    int n = equipos.size();
    int W = 10;
    cout<<"Beneficio máximo"<<endl;
    cout<<multipleChoiceKnapsack(equipos, n, W)<<endl;


    return 0;
}