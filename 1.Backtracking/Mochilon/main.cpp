#include <iostream>

using namespace std;

bool mochilaBack(int idx,int acumulado,int *paq,int  n,int peso) {
    if (acumulado == peso) {
        return true;
    }
    if (idx==n or acumulado>peso) return false;

    if (mochilaBack(idx+1,acumulado+paq[idx],paq,n,peso)) {
        return true;
    }else {
        return mochilaBack(idx+1,acumulado,paq,n,peso);
    }
    return false;
}


int main() {
    int paq[] = {5,2,1,4,3,2};
    int peso = 10;
    int n = sizeof(paq)/sizeof(paq[0]);
    cout<<mochilaBack(0,0,paq, n, peso);
    return 0;
}
