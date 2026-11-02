#include <iostream>

using namespace std;

bool empaca(int i,int n,int peso,int *paq,int acumulado) {
    if (acumulado==peso) {
        return true;
    }
    if (acumulado>peso or i==n) {
        return false;
    }
    //avanzo en el arreglo
    if (empaca(i+1,n,peso,paq,acumulado+paq[i])) {
        return true;
    }else {
        return empaca(i+1,n,peso,paq,acumulado);
    }

}

int main() {
    int paq[]={5,10,4,2};
    int peso=16;
    int n=sizeof(paq)/sizeof(paq[0]);
    int acumulado=0;
    if (empaca(0,n,peso,paq,acumulado)) {
        cout<<"Se puede llenar la mochila con el peso de "<<peso<<endl;
    }else {
        cout<<"No hay solucion"<<endl;
    }
    return 0;
}