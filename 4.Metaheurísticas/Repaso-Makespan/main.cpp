#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*Makespan
 *
 * Se tiene N tareas en un linea de produccion
 * y se tienen que ejecutar con M maquinas
 *
 * Cada tarea demora un tiempo Ti en ser ejecutada por una maquina
 *
 * El problema consiste en ejecutar las tareas procurando
 * MINIMIZAR el tiempo ocioso de las M maquinas
 *
 * el tiempo maximo de trabajo acumulado es el makespan
 *
 */

void programarTelares(int *telas,int n,int k,int *tiempos) {
    //k = 3, n = 6
    int cargaTrabajo[k]; //tiene 3 espacios para cada maquina
    fill(cargaTrabajo,cargaTrabajo+k,0); //carga de trabajo de cada maquina
    int Asignaciones[k][n]; //asignaciones de telas a cada maquina
    int contadorAsignaciones[k]; //contador de las telas asignadas a cada maquina
    fill(contadorAsignaciones,contadorAsignaciones+k,0);

    //tarea por cada maquina
    for (int i=0;i<n;i++) {
        int minIndice=0; //asumimos que la maquina 0 no demora para poder realizar las comparaciones con las demás maquinas
        int minTiempo = cargaTrabajo[0]+telas[i]*tiempos[0];
        //comparamos con las demás maquinas
        for (int j=1;j<k;j++) {
            //la carga de la maquina actual es decir la 1, no la 0
            if (cargaTrabajo[j]+telas[i]*tiempos[j]<minTiempo) {
                minIndice=j;//guardamos el menor indice
                minTiempo = cargaTrabajo[j]+telas[i]*tiempos[j];
            }
        }
        //guardo en el que considero el menor tiempo de ejecucion de una tarea(maquina)
        //el valor de esa tela multiplicado por su tiempo de esa maquina que sería el menor indice
        cargaTrabajo[minIndice]+= telas[i]*tiempos[minIndice];
        //finalmente lo guardamos en la matriz
        Asignaciones[minIndice][contadorAsignaciones[minIndice]++]=telas[i];
        //guardo en el que considero la maquina que acaba más rapido de ejecutar la tarea, como se trata de un arreglo
        //la variable de menor indice cumple su rol como una variable de contador?
        //para poder guardar el valor de esa tela
    }
    //aclaraciones de Gemini
    /* minIndice++ cambia el indice de la maquina
     * contadorAsignaciones[minIndice]++ cambia la cantidad de telas que tiene la maquina ganadora
     */

    cout<<"Asignaciones de telas a las maquinas"<<endl;
    for (int i=0; i<k ; i++) {
        cout<<"Telar"<<i<<" : ";
        for (int j=0; j<contadorAsignaciones[i]; j++) {
            cout<<Asignaciones[i][j]<<(j<contadorAsignaciones[i]-1? " , ":" ");
        }
        cout<<"- Tiempo total de trabajo: "<<cargaTrabajo[i]<<" unidades de tiempo"<<endl;
    }
    int maxCargaTrabajo = *max_element(cargaTrabajo,cargaTrabajo+n);
    cout<<"Tiempo minimo para terminar todas las telas: "<<maxCargaTrabajo<<" unidades de tiempo"<<endl;
}

int main() {
    int T = 5; //tiempo de metro por la TELA
    int k = 3; //número de telares -> maquinas
    int n = 6; //número de telas
    int telas[] = {10,7,8,12,6,9};
    int tiempos[] = {5,4,6};

    programarTelares(telas,n,k,tiempos);

    return 0;
}


/*
* //recorremos las telas
    for (int i=0;i<n;i++) {
        //encuentra la maquina que tiene la menor carga de trabajo actual
        int minIndice=0;
        int minTiempoFinal = cargaTrabajo[0] + telas[i]*tiempos[0];
        //recorremos las maquinas k=3
        for (int j=1; j<k; j++) { //analizamos cada maquina restantes pues asumimos la maquina 0
            if (cargaTrabajo[j] + telas[i]*tiempos[j] < minTiempoFinal) {
                minIndice = j;
                minTiempoFinal = cargaTrabajo[j]+telas[i]*tiempos[j];
            }
        }
        //asignamos la tela actual a la maquina con la menor carga de trabajo actual
        cargaTrabajo[minIndice] += telas[i]*tiempos[minIndice];
        Asignaciones[minIndice][contadorAsignaciones[minIndice]++]=telas[i];
    }
 */