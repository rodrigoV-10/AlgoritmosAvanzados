#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Producto {
    int latas;
    int longitud;
    int altura;
};

bool compara(Producto p1, Producto p2) {
    return p1.longitud*p1.altura > p2.longitud*p2.altura;
}

void cortarLaminas(vector<Producto>&productos,int n,int areaTotal) {
    sort(productos.begin(),productos.end(),compara);
    int laminas = 1;
    int cantidad_sobra=areaTotal;
    int areaUtilizada=0;
    for (int i=0;i<n;i++) { //recorremos la cantidad de productos
        Producto p = productos[i];
        int area = p.longitud*p.altura; //area que se usa para una lata
        //como tenemos "n" latas entonces iteramos hasta esa cantidad de "n" latas
        for (int j = 0 ; j<p.latas ; j++) {
            //si el area que obtenemos es menor que el area que tiene cada lámina
            if (area<=cantidad_sobra) {
                //entonces actualizamos su area o mejor dicho le restamos ese corte
                cantidad_sobra -=area;
            }else {
                //caso contrario incrementamos la cantidad de laminas
                laminas++;
                //el area de esta lamina es igual a 2500 que sería el areaTotal
                cantidad_sobra = areaTotal;
                //y luego restamos el area a esta nueva lamina
                cantidad_sobra-=area;
            }
            //finalmente sumamos el area utilizada
            areaUtilizada +=area;
        }
    }
    int areaDisponible = laminas*areaTotal;
    int merma = areaDisponible-areaUtilizada;
    double porcentajeMerma = ((double)merma/areaDisponible)*100;
    cout<<"Cantidad de laminas usadas: "<<laminas<<endl;
    cout<<"Cantidad de mermas: "<<merma<<endl;
    cout<<"Porcentaje de merma: "<<porcentajeMerma<<"%"<<endl;
}


int main() {
    vector<Producto> productos;
    productos = {
        {5,2,3},
        {10,9,3},
        {15,14,7},
        {20,15,20},
        {20,22,18},
    };
    int n= productos.size();
    int areaTotal = 50*50;

    cortarLaminas(productos,n,areaTotal);

    return 0;
}
