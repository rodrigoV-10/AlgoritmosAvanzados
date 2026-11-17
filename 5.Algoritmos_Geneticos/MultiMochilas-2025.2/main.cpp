#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 5
#define NUMIND 10
#define TSELECCION 0.3
#define PCASAMIENTO 0.5
#define TMUTACION 0.3

using namespace  std;

int calculafitness(vector<int>cromo,int* camiones,int* paq,int numCam,int numPaq) {
    int sumaTotal=0;
    //por cada camion, calculamos y verificamos que no se pase
    for (int t=0; t<numCam; t++) {
        int uso=0;
        //chapo un camion
        int capacidad_de_un_camion = camiones[t];
        //recorro los paquetes
        for (int p=0; p<numPaq; p++) {
            int idx = t*numPaq+p; //posicion en el cromosoma
            if (cromo[idx]==1) {
                uso+=paq[p];
            }
        }
        //si se pasa de la capacidad, fitness = 0 (solucion inválida)
        if (uso>capacidad_de_un_camion) {
            return 0;
        }
        sumaTotal+=uso;
    }
    //si no se asignó nada, no es una buena solución
    if (sumaTotal==0)return 0;
    //mientras mayor sea el uso total, menos es el desperdicio
    return sumaTotal;
}

bool aberracion(vector<int>ind,int* camiones,int* paq,int numCam,int numPaq) {
    //verificamos la capacidad por camion
    for (int c = 0 ; c < numCam; c++) {
        int acumulado=0; //se reinicia pues es por cada camion
        int capacidad_camion = camiones[c];
        //recorremos los paquetes
        for (int p = 0 ; p < numPaq; p++) {
            int idx = c*numPaq+p;
            if (ind[idx]==1) {
                acumulado+=paq[p];
            }
        }
        if (acumulado>capacidad_camion) {
            return true; //es una aberracion
        }
    }
    //verificamos que un paquete solo este en un camion
    for (int p=0;p<numPaq;p++) {
        int contador=0;
        for (int c=0; c<numCam; c++) {
            int idx = c*numPaq+p;
            if (ind[idx]==1) {
                contador++;
            }
        }
        //si aparece en más de un camion retornamos true pues es una aberracion
        if (contador!=1) return true;
    }
    return false;
}

void muestrapoblacion(vector<vector<int>>poblacion,int* camiones,int* paq,
    int numCam,int numPaq) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],camiones,paq,numCam,numPaq)<<endl;
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
    int* camiones,int* paq,int numCam,int numPaq) {
    int cont=0;
    int cromoTam = numCam*numPaq;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int> individuo;
        // aqui también cambiar
        for (int i=0; i<cromoTam; i++)
            individuo.push_back(rand()%2);
        if (!aberracion(individuo,camiones,paq,numCam,numPaq)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,int* camiones,int* paq,int numCam,int numPaq) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],camiones,paq,numCam,numPaq);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],camiones,paq,numCam,numPaq)/sumafitness);
        supervivencia.push_back(superfit);
    }
}
void cargaruleta(vector<int >supervivencia,int *ruleta) {
    int cont = 0;
    for (int i = 0; i < (int)supervivencia.size() && cont < 100; i++) {
        for (int j = 0; j < supervivencia[i] && cont < 100; j++) {
            ruleta[cont++] = i;
        }
    }
    while (cont < 100) {
        ruleta[cont++] = -1;
    }
}



void seleccion(vector<vector<int>>poblacion,vector<vector<int>> &padres,
   int* camiones,int* paq,int numCam,int numPaq) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,camiones,paq,numCam,numPaq);
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
    int* camiones,int* paq,int numCam,int numPaq) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,camiones,paq,numCam,numPaq))
                    poblacion.push_back(hijo);
            }


        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        int *camiones,int* paq,int numCam,int numPaq){
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [camiones,paq,numCam,numPaq](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
            for(int i=0;i<a.size();i++)
                suma += calculafitness(a,camiones,paq,numCam,numPaq);
            for(int i=0;i<b.size();i++)
                sumb += calculafitness(b,camiones,paq,numCam,numPaq);

            return suma > sumb;
         });
    if (poblacion.size()>NUMIND)
        poblacion.erase(poblacion.begin()+NUMIND,poblacion.end());

}

void mutacion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int *camiones,int* paq,int numCam,int numPaq) {
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
        if (!aberracion(padres[i],camiones,paq,numCam,numPaq))
            poblacion.push_back(padres[i]);
    }
}

void inversion(vector<vector<int>> &poblacion,vector<vector<int>>padres,
    int *camiones,int* paq,int numCam,int numPaq) {

    for (int i=0;i<padres.size();i++) {
        for (int j=0;j<padres[i].size();j++) {
            //cambiar para numeros enteros
            if (padres[i][j]==0) padres[i][j]=1;
            else padres[i][j]=0;
        }
        if (!aberracion(padres[i],camiones,paq,numCam,numPaq))
            poblacion.push_back(padres[i]);
    }
}

int muestramejor(const vector<vector<int>> &poblacion,
                 int *camiones,int* paq,int numCam,int numPaq){
    int mejor = 0;

    for (int i = 1; i < (int)poblacion.size(); i++)
        if (calculafitness(poblacion[i],camiones,paq,numCam,numPaq) >
            calculafitness(poblacion[mejor],camiones,paq,numCam,numPaq))
            mejor = i;

    int mejorFit = calculafitness(poblacion[mejor],camiones,paq,numCam,numPaq);
    cout << endl << "La mejor solucion tiene fitness (peso total usado): "
         << mejorFit << endl;
    cout << "Cromosoma: ";
    for (int i = 0; i < (int)poblacion[mejor].size(); i++)
        cout << poblacion[mejor][i] << " ";
    cout << endl;

    // Mostrar asignación por camión y desperdicio
    int desperdicioTotal = 0;
    int sumaCap = 0;

    cout << "\nAsignación de paquetes a camiones:" << endl;
    for (int t = 0; t < numCam; t++) {
        int uso = 0;
        cout << "Camion " << t+1 << " (capacidad " << camiones[t] << "): ";
        for (int p = 0; p < numPaq; p++) {
            int idx = t * numPaq + p;
            if (poblacion[mejor][idx] == 1) {
                cout << "P" << (p+1) << " ";
                uso += paq[p];
            }
        }
        int desp = camiones[t] - uso;
        desperdicioTotal += desp;
        sumaCap += camiones[t];
        cout << "  [uso=" << uso << ", desperdicio=" << desp << "]" << endl;
    }

    cout << "DESPERDICIO TOTAL = " << desperdicioTotal
         << " de " << sumaCap << " kg de capacidad." << endl;

    return desperdicioTotal;
}

void mochilaAG(int *camiones,int *paq,int numCam,int numPaq) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,camiones,paq,numCam,numPaq);

    for(int i=0;i<ITERACIONES;i++) {
        cout<<"ITERACION: "<<i+1<<endl;
        vector<vector<int>>padres;
        //muestrapoblacion(poblacion,camiones,paq,numCam,numPaq);
        //cout << endl;
        seleccion(poblacion,padres,camiones,paq,numCam,numPaq);
        casamiento(poblacion,padres,camiones,paq,numCam,numPaq);
        mataclon(poblacion);
        //mutacion((poblacion),padres,camiones,paq,numCam,numPaq);
        //inversion(poblacion,padres,camiones,paq,numCam,numPaq);
        regenerapoblacion(poblacion,camiones,paq,numCam,numPaq);
        muestrapoblacion(poblacion,camiones,paq,numCam,numPaq);
        //muestramejor(poblacion,camiones,paq,numCam,numPaq);
        cout<<"--------------------------------------"<<endl;
    }
    muestramejor(poblacion,camiones,paq,numCam,numPaq);
}

int main() {
    //multimochilas
    int camiones[] = {250,200,200,100};
    int numCam = sizeof(camiones)/sizeof(camiones[0]);
    int paq[]={150,100,180,50,120,10};
    int numPaq=sizeof(paq)/sizeof(paq[0]);
    mochilaAG(camiones,paq,numCam,numPaq);
    //mochilaAG(paq,n,peso);

    return 0;
}