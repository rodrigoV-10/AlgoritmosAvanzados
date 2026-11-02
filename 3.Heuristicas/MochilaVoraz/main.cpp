#include <iostream>
#include <algorithm>

using namespace std;

bool compara(int a, int b) {
    //como queremos maximizar la cantidad de paquetes
    //hacemos que entre la mayor cantidad de paquetes
    //desde los más ligeros hasta los más grandes
    return a < b;
}

// ascendente a < b
// descendente a > b

int cargaMochila(int *paq,int n,int peso) {
    int residuo = peso;
    sort(paq, paq+n, compara);
    for (int i=0 ; i<n ; i++) {
        if (residuo-paq[i]>=0) {
            residuo -= paq[i];
        }
    }
    return residuo;
}


int main() {
    //queremos maximizar la cantidad de paquetes
    int paq[] = {3 , 2 , 2, 10 , 4};
    int peso= 15;
    int n = sizeof(paq)/sizeof(paq[0]);

    cout<<"Espacio que sobra: "<< cargaMochila(paq,n,peso)<<endl;

    return 0;
}
