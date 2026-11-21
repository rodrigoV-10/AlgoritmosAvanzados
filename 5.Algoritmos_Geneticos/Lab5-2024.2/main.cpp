#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 10
#define NUMIND 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.8
#define TMUTACION 0.3
#define N 5

using namespace  std;

int calculafitness(vector<int>cromo,int matriz[N][N],int n) {
    int sumap=0;
    for (int tarea=0;tarea<n;tarea++) {
        for (int empleado=0; empleado<n; empleado++) {
            int idx = tarea*n+empleado;
            if (cromo[idx]==1) {
                sumap+=matriz[tarea][empleado];
            }
        }
    }
    return sumap;
}

bool aberracion(vector<int>ind,int matrizGanancia[N][N],int n) {
    //tenemos que evitar que se solapen, es decir una tarea para cada uno de los empleados
    //entonces por cada 5 bits es una tarea y solo 1 bit tiene que quedar marcado , pues es un empleado
    //cada tarea debe tener solo un empleado
    for (int tarea=0;tarea<n;tarea++) {
        int contador_por_tarea=0;
        for (int empleado=0; empleado<n; empleado++) {
            int idx = tarea*n+empleado;
            if (ind[idx]==1) {
                contador_por_tarea++;
            }
        }
        //signigica que fue asignado a más de un empleado
        if (contador_por_tarea!=1) {
            return true;
        }
    }
    //cada empleado solo debe tener una tarea
    for (int empleado=0; empleado<n; empleado++) {
        int cont=0;
        for (int tarea=0; tarea<n; tarea++) {
            int idx = tarea*n+empleado;
            if (ind[idx]==1) {
                cont++;
            }
        }
        if (cont!=1) {
            return true;
        }
    }
    return false;
}

void muestrapoblacion(vector<vector<int>>poblacion,int matrizGanancia[N][N],
    int n) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],matrizGanancia,n)<<endl;
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
    int matrizGanancia[N][N],int n) {
    int cont=0;
    //int cromotam=N*N;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int> individuo(N*N,0);
        // aqui también cambiar
        for (int tarea=0; tarea<N; tarea++) {
            int empleado=rand()%N;
            int idx = tarea*n+empleado;
            individuo[idx]=1;
        }
        if (!aberracion(individuo,matrizGanancia,N)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,int matrizGanancia[N][N],int n) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],matrizGanancia,n);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],matrizGanancia,n)/sumafitness);
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
   int matrizGanancia[N][N],int n) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,matrizGanancia,n);
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
    int matrizGanancia[N][N],int n) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,matrizGanancia,n))
                    poblacion.push_back(hijo);
            }
        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        int matrizGanancia[N][N],int n){
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [matrizGanancia,n](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
            for(int i=0;i<a.size();i++)
                suma += calculafitness(a, matrizGanancia,n);
            for(int i=0;i<b.size();i++)
                sumb += calculafitness(b, matrizGanancia,n);

            return suma > sumb;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());

}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matrizGanancia[N][N],int n) {
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
        if (!aberracion(padres[i],matrizGanancia,n))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matrizGanancia[N][N],int n) {

    for (int i=0;i<padres.size();i++) {
        for (int j=0;j<padres[i].size();j++) {
            //cambiar para numeros enteros
            if (padres[i][j]==0) padres[i][j]=1;
            else padres[i][j]=0;
        }
        if (!aberracion(padres[i],matrizGanancia,n))
            poblacion.push_back(padres[i]);
    }
}

void muestramejor(vector<vector<int>> poblacion,
        int matrizGanancia[N][N],int n){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],matrizGanancia,n)<calculafitness(poblacion[i],matrizGanancia,n))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],matrizGanancia,n)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    // cout << endl;
    // return peso-calculafitness(poblacion[mejor],paq);
}

void mochilaAG(int matrizGanancia[N][N],int n) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,matrizGanancia,n);

    for(int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        //muestrapoblacion(poblacion,matrizGanancia,n);
        cout << endl;
        seleccion(poblacion,padres,matrizGanancia,n);
        casamiento(poblacion,padres,matrizGanancia,n);
        mataclon(poblacion);
        mutacion((poblacion),padres,matrizGanancia,n);
        mataclon(poblacion);
        inversion(poblacion,padres,matrizGanancia,n);
        mataclon(poblacion);
        regenerapoblacion(poblacion,matrizGanancia,n);
        muestrapoblacion(poblacion,matrizGanancia,n);
    }
    muestramejor(poblacion,matrizGanancia,n);
}

int main() {
    // int paq[]={1,2,2,12,4};
    // int n=sizeof(paq)/sizeof(paq[0]);
    // int peso=15;
    //
    //
    int matrizGanancia[N][N] = {
        {9,2,7,8,6},
        {6,4,3,7,8},
        {5,8,1,8,3},
        {7,6,9,4,2},
        {8,6,7,5,9}
    };
    mochilaAG(matrizGanancia,N);
    return 0;
}