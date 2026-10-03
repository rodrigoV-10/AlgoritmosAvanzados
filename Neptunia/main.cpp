#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
struct Paquete {
    int id;
    int ganancia;
    int peso;
};
//maximizar ganancia y minimizar peso
bool compara(Paquete p1, Paquete p2) {
    return (double)p1.ganancia/p1.peso > (double)p2.ganancia/p2.peso;
}


int neptunia(vector<Paquete>&paquetes,int n,int pesomax) {
    int sobra=pesomax;
    int ganancia=0;
    sort(paquetes.begin(),paquetes.end(),compara);
    for (int i=0;i<n;i++) {
        Paquete paq = paquetes[i];
        if (sobra-paq.peso>=0) {
            sobra-=paq.peso;
            ganancia+=paq.ganancia;
        }
    }
    cout<<"El peso sobrando en el contenedor es: "<<sobra<<endl;
    return ganancia;
}


int main() {
    vector<Paquete> paquetes;
    paquetes={
            {1,10,2},
            {2,15,3},
            {3,10,5},
            {4,14,12},
            {5,8,2},
            {6,5,5},
    };
    int n=paquetes.size();
    int pesomax=20;
    cout<<neptunia(paquetes,n,pesomax)<<endl;
    return 0;
}
