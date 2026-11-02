#include <iostream>
#include <vector>

using namespace std;
#define N 4
#define M 5

bool backtrack_una_solucion(int idx,vector<int>&productos,
    vector<int>&rack_ubicaciones,vector<int>&unaSolucion) {
    if (idx==productos.size()) {
        return true;
    }
    for (int i=0;i<rack_ubicaciones.size();i++) {
        //en la pos de una solucion
        if (unaSolucion[i]+productos[idx]<=rack_ubicaciones[i]) {
            unaSolucion[i]+=productos[idx];
            if (backtrack_una_solucion(idx+1,productos,
                rack_ubicaciones,unaSolucion)) {
                return true;
            }
            unaSolucion[i]-=productos[idx];
        }
    }
    return false;
}

int main() {
    //el robot debe ser capaz de colocar producots en espacios disponibles
    // y mostrar las cantidades ubicadas luego del proceso

    //los productos recibidos vienen agrupados por cantidades por lo que no peueden dividirse
    //tiene que colocarse en ubicaciones donde puedan contenerlos

    //una ubicacion puede almacenar más de un grupo de productos de un mismo ingreso
    //los ingresos de productos tienen manaño N y la cantidad de ubicaciones
    // del rack es de tamaño M.
    vector<int> productos = {2,3,1,4};
    vector<int>rack_ubicaciones={3,2,5,1,3};
    vector<int> unaSolucion(M,0);
    cout<<"UNA SOLUCION : "<<endl;
    if (backtrack_una_solucion(0,productos,rack_ubicaciones,unaSolucion)) {
        for (int i=0;i<unaSolucion.size();i++) {
            cout<<unaSolucion[i]<<" ";
        }
    }else {
        cout<<"No hay solucion "<<endl;
    }

    vector<vector<int>> soluciones;
    return 0;
}
