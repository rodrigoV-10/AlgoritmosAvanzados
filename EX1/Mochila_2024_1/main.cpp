#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Paquetes {
    int id;
    int ganancia;
    int peso;
};

struct Residuo {
    int ganancia;
    int sobra;
};


//maximizar una ganancia y minimizar costos

int main() {

    Paquetes paq[] = {
        {1,10,2},
        {2,15,3},
        {3,10,5},
        {4,24,12},
        {5,8,2},
    };
    int n = sizeof(paq)/sizeof(Paquetes);
    int pesoMax = 16;



    return 0;
}
