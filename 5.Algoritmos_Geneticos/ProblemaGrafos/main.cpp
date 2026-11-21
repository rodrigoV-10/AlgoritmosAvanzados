#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 10
#define NUMIND 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.5
#define TMUTACION 0.3
#define N 5
using namespace  std;


int calculafitness(vector<int>cromo,int matriz[N][N],int n) {
    int sumap=0;
    for (int origen=0; origen<n; origen++) {
        for (int destino=0; destino<n; destino++) {
            int idx = origen*n+destino;
            if (cromo[idx]==1) {
                sumap+=matriz[origen][destino];
            }
        }
    }
    return sumap;
}

bool aberracion(vector<int>ind,int matriz[N][N],int n) {
    //cada ciudad tiene una salida
    for (int origen=0; origen<n; origen++) {
        int cont=0;
        //no viajar a la misma ciudad
        if (ind[origen*n+origen]==1) return true;

        for (int destino=0; destino<n; destino++) {
            int idx = origen*n+destino;
            if (ind[idx]==1) {
                cont++;
            }
        }
        if (cont!=1) {
            return true;
        }
    }

    //cada ciudad debe tener una unica entrada
    for (int destino=0; destino<n ; destino++) {
        int cont=0;
        for (int origen = 0; origen<n; origen++) {
            int idx = origen*n+destino;
            if (ind[idx]==1) cont++;
        }
        if (cont!=1) return true;
    }

    //se tiene que formar un lazo
    vector<bool> visitado(n,false);
    int actual=0;
    for (int paso=0; paso<n; paso++) {
        //ya pasé por esta ciudad anteriormente?
        if (visitado[actual]) return true;
        //sino marco pues me voy moviendo en mi arreglo de visitados
        visitado[actual]=true;
        //encontrar la siguiente ciudad
        int siguiente=-1;
        for (int destino=0; destino<n ; destino++) {
            int idx = actual*n+destino;
            if (ind[idx]==1) {
                siguiente=destino;//hacemos break porque cada ciudad tiene una unica salida, al encontrar el primer bit sabemos
                break; //cual es la unica ciudad siguiente
            }
        }
        if (siguiente==-1) return true;
        actual=siguiente;
    }

    return actual!=0;
}

void muestrapoblacion(vector<vector<int>>poblacion,int matriz[N][N],int n) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],matriz,n)<<endl;
    }

}

int decimal(vector<int>ind) {
    int num=0;
    for (int i=0;i<ind.size();i++)
        num+=ind[i]*pow(2,i);
    return num;
}

void mataclon(vector<vector<int>> &poblacion) {
    map<int,vector<int>> indunicos;

    for(int i=0;i<poblacion.size();i++) {
        int dec=decimal(poblacion[i]);
        indunicos[dec]=poblacion[i];
    }
    poblacion.clear();
    for(map<int,vector<int>>::iterator it=indunicos.begin();
        it!=indunicos.end();it++) {
        poblacion.push_back(it->second);
    }
}

//para este problema de grafos hay problemas con este genera poblacion
// void generapoblacion(vector<vector<int>> &poblacion,
//     int matriz[N][N],int n){
//     int cont=0;
//     int cromoTam = N*N;
//     srand(time(NULL));
//     while (cont<NUMIND) {
//         vector<int> individuo;
//         // aqui también cambiar
//         for (int i=0; i<cromoTam; i++)
//             individuo.push_back(rand()%2);
//         if (!aberracion(individuo,matriz,n)) {
//             poblacion.push_back(individuo);
//             cont++;
//         }
//     }
// }

void generapoblacion(vector<vector<int>>& poblacion,
                    int matriz[N][N], int n) {

    int cont = 0;
    while (cont < NUMIND) {
        // Cromosoma de 25 bits inicializado en 0
        vector<int> individuo(n * n, 0);
        // Controlamos las ciudades visitadas
        vector<bool> visitados(n, false);
        int actual = 0;
        visitados[actual] = true;
        // Tenemos que visitar las otras N-1 ciudades
        for (int paso = 1; paso < n; paso++) {
            int siguiente;
            // Buscar aleatoriamente una ciudad no visitada
            do {
                siguiente = rand() % n;
            } while (visitados[siguiente]);
            // Activar la conexion actual -> siguiente
            int idx = actual * n + siguiente;
            individuo[idx] = 1;
            // Marcar la ciudad elegida
            visitados[siguiente] = true;
            // Nos movemos a la siguiente ciudad
            actual = siguiente;
        }
        // Regresar desde la ultima ciudad hacia la ciudad 0
        individuo[actual * n + 0] = 1;
        // Verificar que sea un individuo valido
        if (!aberracion(individuo, matriz, n)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,int matriz[N][N],int n) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],matriz,n);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],matriz,n)/sumafitness);
        supervivencia.push_back(superfit);
    }
}
void cargaruleta(vector<int >supervivencia,int *ruleta) {
    int cont=0;
    for (int i=0;i<supervivencia.size() && cont<100;i++)
        for (int j=0;j<supervivencia[i] && cont<100;j++) {
            ruleta[cont++]=i;
        }
    while (cont<100) {
        ruleta[cont++]=-1;
    }
}



void seleccion(vector<vector<int>>poblacion,vector<vector<int>> &padres,
   int matriz[N][N],int n) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,matriz,n);
    cargaruleta(supervivencia,ruleta);
    int npadres=round(poblacion.size()*TSELECCION);

    for (int i=0;i<npadres;i++) {
        int ticket=rand()%100;
        if (ruleta[ticket]!=-1)
            padres.push_back(poblacion[ruleta[ticket]]);
    }
    //muestrapoblacion(padres,paq);
}

void creahijo(vector<int>padre,vector<int>madre,
    vector<int>&hijo) {
    int posi=round(padre.size()*PCASAMIENTO);

    for (int i=0;i<posi;i++)
        hijo.push_back(padre[i]);
    for (int i=posi;i<madre.size();i++)
        hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[N][N],int n) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,matriz,n))
                    poblacion.push_back(hijo);
            }
        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        int matriz[N][N],int n){
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [matriz,n](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
             suma += calculafitness(a, matriz,n);
             sumb += calculafitness(b, matriz,n);

            return suma < sumb;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());

}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[N][N],int n) {
    int nmutaciones=round(padres[0].size()*TMUTACION);
    for (int i=0;i<padres.size();i++) {
        int cont=0;
        while (cont<nmutaciones) {
            int gen=rand()%padres[i].size();
            //aqui hay que cambiar si son numeros enteros
            if (padres[i][gen]==0) padres[i][gen]=1;
            else padres[i][gen]=0;
            cont++;
        }
        if (!aberracion(padres[i],matriz,n))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[N][N],int n) {

    for (int i=0;i<padres.size();i++) {
        for (int j=0;j<padres[i].size();j++) {
            //cambiar para numeros enteros
            if (padres[i][j]==0) padres[i][j]=1;
            else padres[i][j]=0;
        }
        if (!aberracion(padres[i],matriz,n))
            poblacion.push_back(padres[i]);
    }
}

void muestramejor(vector<vector<int>> poblacion,
        int matriz[N][N],int n){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[i],matriz,n)<calculafitness(poblacion[mejor],matriz,n))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],matriz,n)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    cout << endl;
    // return peso-calculafitness(poblacion[mejor],paq);
}

void mochilaAG(int matriz[N][N],int n) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,matriz,n);

    for(int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        muestrapoblacion(poblacion,matriz,n);
        // cout << endl;
        seleccion(poblacion,padres,matriz,n);
        casamiento(poblacion,padres,matriz,n);
        mataclon(poblacion);
        mutacion((poblacion),padres,matriz,n);
        inversion(poblacion,padres,matriz,n);
        //
        regenerapoblacion(poblacion,matriz,n);
        // muestrapoblacion(poblacion,paq);
        //
    }
    muestramejor(poblacion,matriz,n);
}

int main() {
    /*
    *Enunciado
    La empresa RUTAS EXPRESS S.A.C. necesita optimizar el recorrido
    de un vehículo de reparto que debe visitar cinco ciudades.

    El vehículo comienza su recorrido en la ciudad 0,
    debe visitar todas las demás ciudades exactamente una vez y
    finalmente regresar a su punto de partida.

    Se desea encontrar el recorrido que minimice
    la distancia total recorrida mediante un algoritmo genético.
    */

    /*
    * 3. Restricciones de aberracion()
        Una solución debe cumplir todas estas condiciones:
        1. Cada ciudad tiene exactamente una conexión de salida.
        2. Cada ciudad tiene exactamente una conexión de entrada.
        3. No se permite una conexión de una ciudad hacia sí misma.
        4. Debe formarse un solo ciclo que visite las cinco ciudades.
        5. El recorrido debe regresar a la ciudad 0.
     */
    int distancias[N][N] = {
        { 0, 10, 15, 20, 12},
        {10,  0,  8,  9, 14},
        {15,  8,  0,  7,  6},
        {20,  9,  7,  0, 11},
        {12, 14,  6, 11,  0}
    };
    //como son 5 ciudades cada ciudad puede conectarse con otras
    //los primeros 5 bits son las conexiones que salen de la ciudad 0
    //los siguientes 5 bits son las conexiones que salen de la ciudad 1

    mochilaAG(distancias,N);

    return 0;
}