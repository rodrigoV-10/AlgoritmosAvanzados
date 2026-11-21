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
#define TRABAJADORES 3
#define TAREAS 4

using namespace  std;

int calculafitness(vector<int>cromo,int matriz[TRABAJADORES][TAREAS],
    int cant_TRABAJADORES,int cant_TAREAS) {
    int sumap=0;
    for (int i=0;i<cant_TRABAJADORES;i++) {
        for (int j=0;j<cant_TAREAS;j++) {
            int idx = i*cant_TAREAS+j;
            if (cromo[idx]==1) {
                sumap+=matriz[i][j];
            }
        }
    }
    return sumap;
}

bool aberracion(vector<int>ind,int matriz[TRABAJADORES][TAREAS],
    int cant_TRABAJADORES,int cant_TAREAS) {
    //cada tarea debe tener un trabajador
    for (int tarea=0;tarea<cant_TAREAS;tarea++) {
        int cont=0;
        for (int trabajador=0; trabajador<cant_TRABAJADORES; trabajador++) {
            int idx = trabajador*cant_TAREAS+tarea;
            if (ind[idx]==1) {
                cont++;
            }
        }
        if (cont!=1) return true;
    }
    //cada empleado solo debe de estar en una tarea
    for (int trabajador=0; trabajador<cant_TRABAJADORES; trabajador++) {
        int cont_empleado=0;
        for (int tareas=0; tareas<cant_TAREAS; tareas++) {
            int idx = trabajador*cant_TAREAS+tareas;
            if (ind[idx]==1) {
                cont_empleado++;
            }
        }
        if (cont_empleado>2)return true;
    }
    return false;
}

void muestrapoblacion(vector<vector<int>>poblacion,int matriz[TRABAJADORES][TAREAS],
    int cant_trabajadores,int cant_tareas) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],matriz,cant_trabajadores,cant_tareas)<<endl;
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
    int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS) {
    int cont=0;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int> individuo(TRABAJADORES*TAREAS,0);
        // aqui también cambiar
        for (int tarea=0; tarea<cant_TAREAS; tarea++) {
            int trabajador = rand()%TRABAJADORES;
            int idx = trabajador*cant_TAREAS+tarea;
            individuo[idx]=1;
        }
        if (!aberracion(individuo,matriz,cant_TRABAJADORES,cant_TAREAS)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,int matriz[TRABAJADORES][TAREAS],
    int cant_TRABAJADORES,int cant_TAREAS) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],matriz,cant_TRABAJADORES,cant_TAREAS);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],matriz,cant_TRABAJADORES,cant_TAREAS)/sumafitness);
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
   int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,matriz,cant_TRABAJADORES,cant_TAREAS);
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
    int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,matriz,cant_TRABAJADORES,cant_TAREAS))
                    poblacion.push_back(hijo);
            }
        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS){
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [matriz,cant_TRABAJADORES,cant_TAREAS](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
             suma = calculafitness(a, matriz,cant_TRABAJADORES,cant_TAREAS);
             sumb = calculafitness(b, matriz,cant_TRABAJADORES,cant_TAREAS);
            return suma < sumb;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());

}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS) {
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
        if (!aberracion(padres[i],matriz,cant_TRABAJADORES,cant_TAREAS))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS) {

    for (int i=0;i<padres.size();i++) {
        for (int j=0;j<padres[i].size();j++) {
            //cambiar para numeros enteros
            if (padres[i][j]==0) padres[i][j]=1;
            else padres[i][j]=0;
        }
        if (!aberracion(padres[i],matriz,cant_TRABAJADORES,cant_TAREAS))
            poblacion.push_back(padres[i]);
    }
}

void muestramejor(vector<vector<int>> poblacion,
        int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[i],matriz,cant_TRABAJADORES,cant_TAREAS)<calculafitness(poblacion[mejor],matriz,cant_TRABAJADORES,cant_TAREAS))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],matriz,cant_TRABAJADORES,cant_TAREAS)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    cout << endl;
    // return peso-calculafitness(poblacion[mejor],paq);
}

void mochilaAG(int matriz[TRABAJADORES][TAREAS],int cant_TRABAJADORES,int cant_TAREAS) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,matriz,cant_TRABAJADORES,cant_TAREAS);

    for(int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        muestrapoblacion(poblacion,matriz,cant_TRABAJADORES,cant_TAREAS);
        //cout << endl;
        seleccion(poblacion,padres,matriz,cant_TRABAJADORES,cant_TAREAS);
        casamiento(poblacion,padres,matriz,cant_TRABAJADORES,cant_TAREAS);
        mataclon(poblacion);
        mutacion((poblacion),padres,matriz,cant_TRABAJADORES,cant_TAREAS);
        inversion(poblacion,padres,matriz,cant_TRABAJADORES,cant_TAREAS);
        //
        regenerapoblacion(poblacion,matriz,cant_TRABAJADORES,cant_TAREAS);
        // muestrapoblacion(poblacion,paq);
    }
    muestramejor(poblacion,matriz,cant_TRABAJADORES,cant_TAREAS);
}

int main() {
    // int paq[]={1,2,2,12,4};
    // int n=sizeof(paq)/sizeof(paq[0]);
    // int peso=15;
    //
    int matriz[TRABAJADORES][TAREAS]={
        {9,6,4,8},
        {5,7,6,3},
        {8,5,7,4},
    };
    mochilaAG(matriz,TRABAJADORES,TAREAS);

    return 0;
}