#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

#define ITERACIONES 100000
#define ALFA 0.3


using namespace std;


struct Sobjeto {
    int codigo;
    int velocidad;
    int capacidad;
};

struct Ssolucion {
    int disco;
    int tabla;
};

bool compara (Sobjeto a, Sobjeto b) {
    //descendente 3,2,1...
    return a.velocidad > b.velocidad;
}

int calcularRCL(vector<Sobjeto> arreglo,double rcl) {
    int contador = 0;
    for (int i = 0; i < arreglo.size(); i++) {
        if (arreglo[i].velocidad >= rcl) {
            contador++;
        }
    }
    return contador;
}

//pregunta es maximización o minimización?
void cargaDisco(Sobjeto *tabla,Sobjeto *disco,int n,int m) {
    //el disco se ordena cada vez que es asignado a una tabla sort()
    int mejor = INT_MIN; //luego lo analizo -> maximización
    vector<Ssolucion> mejorSolucion;
    srand(time(NULL));
    for (int i=0; i<ITERACIONES; i++) {
        vector<Ssolucion> soluciones;
        vector<Sobjeto> vTabla;
        vector<Sobjeto> vDisco;
        int residual;
        vTabla.insert(vTabla.begin(),tabla,tabla+n);
        vDisco.insert(vDisco.begin(),disco,disco+m);
        //sort del disco
        sort(vTabla.begin(),vTabla.end(),compara);
        //calculo del RCL bla bla bla
        while (!vTabla.empty()) {
            //RCL TABLA
            int betaTabla = vTabla[0].velocidad;
            int taoTabla = vTabla[vTabla.size()-1].velocidad;
            double rclTabla = betaTabla-ALFA*(betaTabla-taoTabla);
            //depdende de mi RCL entonces veo si el contador es mayor o menor igual que el RCL
            int cantidad_rclTabla = calcularRCL(vTabla,rclTabla);
            if (cantidad_rclTabla==0) break;
            int indiceAleatorioTabla = rand()%cantidad_rclTabla;
            //RCL DISCO
            sort(vDisco.begin(),vDisco.end(),compara);
            int betaDisco = vDisco[0].velocidad;
            int taoDisco = vDisco[vDisco.size()-1].velocidad;
            double rclDisco = betaDisco-ALFA*(betaDisco-taoDisco);
            int cantidad_rclDisco = calcularRCL(vDisco,rclDisco);
            int indiceAleatorioDisco = rand()%cantidad_rclDisco;

            if (vDisco[indiceAleatorioDisco].velocidad>=vTabla[indiceAleatorioTabla].velocidad) {
                soluciones.push_back({vDisco[indiceAleatorioDisco].codigo
                    ,vTabla[indiceAleatorioTabla].codigo});
                vDisco[indiceAleatorioDisco].velocidad-=vTabla[indiceAleatorioTabla].velocidad;
            }
            vTabla.erase(vTabla.begin()+indiceAleatorioTabla);
        }
        sort(vDisco.begin(),vDisco.end(),compara);
        residual = vDisco[vDisco.size()-1].velocidad;
        if (residual>mejor) {
            mejor = residual;
            mejorSolucion.clear();
            mejorSolucion.insert(mejorSolucion.begin(),soluciones.begin(),soluciones.end());
        }
    }
    for (int i=0; i<mejorSolucion.size(); i++) {
        cout << mejorSolucion[i].disco << " " << mejorSolucion[i].tabla<<endl;
    }
    cout<<mejor<<endl;
}

int main() {
    //cuando a una tasa se le asiga el disco , la unidad pierde velocidad
    //comparando el disco de menor velocidad con el disco de menor velocidad del grupo de discos
    Sobjeto tabla[]={
        {1,150,20},
        {2,100,10},
        {3,80,15},
        {4,50,100},
        {5,120,50},
        {6,10,100}
    };
    Sobjeto disco[]={
        {1,250,800},
        {2,200,750},
        {3,200,850}
    };
    int n = sizeof(tabla)/sizeof(tabla[0]);
    int m = sizeof(disco)/sizeof(disco[0]);

    cargaDisco(tabla,disco,n,m);

    return 0;
}
