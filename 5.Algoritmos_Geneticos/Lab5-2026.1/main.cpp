#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <algorithm>
#define ITERACIONES 10
#define NUMIND 20
#define TSELECCION 0.3
#define PCASAMIENTO 0.5
#define TMUTACION 0.3

using namespace  std;

struct Proyecto {
    int id;
    int costo;
    int beneficio;
    vector<int>predecesores;
};

int calculafitness(vector<int>cromo,vector<Proyecto>proyectos,
    int n,int presupuesto) {
    int sumap=0;
    for(int i=0;i<cromo.size();i++) {
        sumap+=cromo[i]*proyectos[i].beneficio;
    }
    return sumap;
}

bool aberracion(vector<int>ind,vector<Proyecto>&proyectos,
    int n,int presupuesto) {
    int costo_total=0;
    //una aberracion es que no tenga el proyecto seleccionado y que pase el presupuesto
    for (int i=0;i<n;i++) {
        if (ind[i]==1) {
            //obtengo el costo de ese proyecto
            costo_total+=proyectos[i].costo;
            //recorro los predecesores de ese proyecto
            for (int j=0; j<proyectos[i].predecesores.size();j++) {
                int id_predecesor = proyectos[i].predecesores[j];
                //si no esta en 1 entonces no ha sido seleccionado
                if (ind[id_predecesor-1]==0) {
                    return true;
                }
            }
        }
    }
    if (costo_total>presupuesto) return true;
    return false;
}

void muestrapoblacion(vector<vector<int>>poblacion,vector<Proyecto>&proyectos,
    int n,int presupuesto) {
    for(int i=0;i<poblacion.size();i++) {
        for(int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<" fo="<< calculafitness(poblacion[i],proyectos,n,presupuesto)<<endl;
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
    vector<Proyecto>&proyectos,int n,int presupuesto) {
    int cont=0;
    srand(time(NULL));
    while (cont<NUMIND) {
        vector<int> individuo;
        // aqui también cambiar
        for (int i=0; i<n; i++)
            individuo.push_back(rand()%2);
        if (!aberracion(individuo,proyectos,n,presupuesto)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void calculasupervivencia(vector<vector<int>>poblacion,
    vector<int> &supervivencia,vector<Proyecto>&proyectos,int n,int presupuesto) {
    int sumafitness=0;

    for(int i=0;i<poblacion.size();i++)
        sumafitness+=calculafitness(poblacion[i],proyectos,n,presupuesto);
    for (int i=0;i<poblacion.size();i++) {
        int superfit;
        superfit=round(100*(double)calculafitness(poblacion[i],proyectos,n,presupuesto)/sumafitness);
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
   vector<Proyecto>&proyectos,int n,int presupuesto) {
    int ruleta[100]{-1};
    vector<int>supervivencia;
    calculasupervivencia(poblacion,supervivencia,proyectos,n,presupuesto);
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
    vector<Proyecto>&proyectos,int n,int presupuesto) {

    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++) {
            if (i!=j) {
                vector<int>hijo;
                creahijo(padres[i],padres[j],hijo);
                if (!aberracion(hijo,proyectos,n,presupuesto))
                    poblacion.push_back(hijo);
            }
        }
}


void regenerapoblacion(vector<vector<int>> &poblacion,
        vector<Proyecto>&proyectos,int n,int presupuesto){
    mataclon(poblacion);
    // se evita emplear variables globales
    sort(poblacion.begin(), poblacion.end(),
         [proyectos,n,presupuesto](const vector<int>& a, const vector<int>& b) {
            int suma=0, sumb=0;
             suma += calculafitness(a, proyectos,n,presupuesto);
             sumb += calculafitness(b, proyectos,n,presupuesto);

            return suma > sumb;
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
        vector<Proyecto>&proyectos,int n,int presupuesto){
    int mejor=0;
    // puede mejorarse ya que esta muestra mejor lo busca en toda la poblaciÃ³n
    // desde luego se puede asumir que es la posiciÃ³n 0 para nuestro caso
    for(int i=0;i<poblacion.size();i++)
        if(calculafitness(poblacion[mejor],proyectos,n,presupuesto)<calculafitness(poblacion[i],proyectos,n,presupuesto))
            mejor=i;

    cout << endl<<"La mejor solucion es:" << calculafitness(poblacion[mejor],proyectos,n,presupuesto)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++)
        cout << poblacion[mejor][i] << "  ";

    cout << endl;
    // return peso-calculafitness(poblacion[mejor],paq);
}

void mochilaAG(vector<Proyecto> &proyectos,int n,int presupuesto) {
    vector<vector<int>> poblacion;
    generapoblacion(poblacion,proyectos,n,presupuesto);

    for(int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        // muestrapoblacion(poblacion,paq);
        // cout << endl;
        seleccion(poblacion,padres,proyectos,n,presupuesto);
        casamiento(poblacion,padres,proyectos,n,presupuesto);
        mataclon(poblacion);
        // mutacion((poblacion),padres,paq,peso);
        // inversion(poblacion,padres,paq,peso);
        //
        regenerapoblacion(poblacion,proyectos,n,presupuesto);
        muestrapoblacion(poblacion,proyectos,n,presupuesto);
    }
    //muestramejor(poblacion,proyectos,n,presupuesto);

    cout<<"Proyectos seleccionados: "<<endl;
    vector<int> mejorProyecto = poblacion[0];
    for (int i=0; i<mejorProyecto.size(); i++) {
        if (mejorProyecto[i]==1) {
            cout<<i+1<<" ";
        }
    }
    cout<<endl;
    cout<<"Beneficio total: "<<calculafitness(mejorProyecto,proyectos,n,presupuesto)<<endl;
}

int main() {
    // int paq[]={1,2,2,12,4};
    // int n=sizeof(paq)/sizeof(paq[0]);
    // int peso=15;
    //
    // mochilaAG(paq,n,peso);
    vector<Proyecto> proyectos={
        {1,100,200,{}},
        {2,50 ,300,{1}},
        {3,150,300,{1}},
        {4,50 ,400,{}},
        {5,50 ,200,{4}},
        {6,150,800,{2,4}},
        {7,100,250,{}},
    };
    int n = proyectos.size();

    int presupuesto=400;
    mochilaAG(proyectos,n,presupuesto);


    return 0;
}