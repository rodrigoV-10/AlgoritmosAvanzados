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
#define N 6
#define K 4

using namespace  std;

//pide minimizar la cantidad de frecuencias utilizadas
//no la cantidad de antenas asignadas
int calculafitness(vector<int>cromo,int grafo[N][N],int n) {
    int frecuenciaUsadas=0;
    for (int frecuencia=0; frecuencia<K ; frecuencia++) {
        bool utilzada=false;
        for (int antena=0; antena<N ; antena++) {
            int idx = frecuencia*N+antena;
            if (cromo[idx]==1) {
                utilzada=true;
                break;
            }
        }
        if (utilzada) {
            frecuenciaUsadas++;
        }
    }
    return frecuenciaUsadas;
}

bool aberracion(vector<int>ind,int grafo[N][N],int n) {
    //cada antena tiene exactamente una frecuencia
    for (int antena=0; antena<N; antena++) {
        int cont=0;
        for (int frecuencia=0; frecuencia<K ; frecuencia++) {
            int idx = frecuencia*N+antena;
            if (ind[idx]==1) {
                cont++;
            }
        }
        if (cont!=1) return true;
    }
    //dos antenas vecinas no pueden compartir frecuencia
    for (int antena=0; antena<N ; antena++) {
        for (int vecino=0; vecino<N; vecino++) {
            if (grafo[antena][vecino]==1) {
                for (int frecuencia=0; frecuencia<K ; frecuencia++) {
                    int idx1 = frecuencia*N+antena;
                    int idx2 = frecuencia*N+vecino;
                    if (ind[idx1]==1 and ind[idx2]==1) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void muestrapoblacion(vector<vector<int>>poblacion,int grafo[N][N],int n) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],grafo,n)<<endl;
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


void generapoblacion(vector<vector<int>> &poblacion,
    int grafo[N][N],int n) {
    int cont=0;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int> individuo(K*N,0);
        // aqui también cambiar
        for (int antena=0; antena<N; antena++) {
            int frecuencia = rand()%K;
            int idx = frecuencia*N+antena;
            individuo[idx]=1;
        }
        if (!aberracion(individuo,grafo,n)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,int grafo[N][N],int n) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],grafo,n);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],grafo,n)/sumafitness);
        supervivencia.push_back(superfit);
    }
}
void cargaruleta(vector<int >supervivencia,int *ruleta) {
    int cont=0;
    for (int i=0;i<supervivencia.size() and cont<100;i++)
        for (int j=0;j<supervivencia[i] and cont<100;j++) {
            ruleta[cont++]=i;
        }
    while (cont<100) {
        ruleta[cont++]=-1;
    }
}



void seleccion(vector<vector<int>>poblacion,vector<vector<int>> &padres,
   int grafo[N][N],int n) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,grafo,n);
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
    int grafo[N][N],int n) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,grafo,n))
                    poblacion.push_back(hijo);
            }
        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        int grafo[N][N],int n){
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [grafo,n](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
             suma += calculafitness(a, grafo,n);
             sumb += calculafitness(b, grafo,n);
            return suma < sumb;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());

}

// void mutacion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
//     int *paq, int peso) {
//     int nmutaciones=round(padres[0].size()*TMUTACION);
//     for (int i=0;i<padres.size();i++) {
//         int cont=0;
//         while (cont<nmutaciones) {
//             int gen=rand()%padres[i].size();
//             //aqui hay que cambiar si son numeros enteros
//             if (padres[i][gen]==0) padres[i][gen]=1;
//             else padres[i][gen]=0;
//             cont++;
//         }
//         if (!aberracion(padres[i],peso,paq))
//             poblacion.push_back(padres[i]);
//     }
// }
//
// void inversion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
//     int *paq, int peso) {
//
//     for (int i=0;i<padres.size();i++) {
//         for (int j=0;j<padres[i].size();j++) {
//             //cambiar para numeros enteros
//             if (padres[i][j]==0) padres[i][j]=1;
//             else padres[i][j]=0;
//         }
//         if (!aberracion(padres[i],peso,paq))
//             poblacion.push_back(padres[i]);
//     }
// }

void muestramejor(vector<vector<int>> poblacion,
        int grafo[N][N],int n){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[i],grafo,n)<calculafitness(poblacion[mejor],grafo,n))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],grafo,n)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    cout << endl;
    // return peso-calculafitness(poblacion[mejor],paq);
}

void mochilaAG(int grafo[N][N],int n) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,grafo,n);

    for(int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        muestrapoblacion(poblacion,grafo,n);
        // cout << endl;
        seleccion(poblacion,padres,grafo,n);
        casamiento(poblacion,padres,grafo,n);
        mataclon(poblacion);
        // mutacion((poblacion),padres,paq,peso);
        // inversion(poblacion,padres,paq,peso);
        //
        regenerapoblacion(poblacion,grafo,n);
        // muestrapoblacion(poblacion,paq);
        // muestramejor(poblacion,grafo,n);
    }
    muestramejor(poblacion,grafo,n);
}

int main() {
    int grafo[N][N] = {
        {0,1,1,0,0,1},
        {1,0,1,0,0,0},
        {1,1,0,1,0,0},
        {0,0,1,0,1,0},
        {0,0,0,1,0,1},
        {1,0,0,0,1,0}
    };

    mochilaAG(grafo,N);
    return 0;
}