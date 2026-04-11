#include <iostream>
#include <vector>
#include <iterator>


using namespace std;

bool validar(int peso,int k,vector<int> unaOrden) {
    if (unaOrden.empty()) {
        return true;
    }
    for (int carne: unaOrden) {
        if (abs(carne-peso)<=k) {
            return true;
        }
    }
    return false;
}

bool construir_orden(int idx,int peso,vector<int>carnes,int k,vector<int> &unaOrden,vector<int> &indice) {
    if (peso==0) {
        return true;
    }

    int unPeso = carnes[idx];
    if (unPeso>peso) {
        return false;
    }

    if (validar(unPeso,k,unaOrden)) {
        unaOrden.push_back(unPeso);
        indice.push_back(idx);
        if (construir_orden(idx+1,peso-unPeso,carnes,k,unaOrden,indice)) {
            return true;
        }
        //backtracking
        unaOrden.pop_back();
        indice.pop_back();
    }
    if (construir_orden(idx+1,peso,carnes,k,unaOrden,indice)) {
        return true;
    }
    return false;
}

int main() {
    vector<int> carnes = {2,8,9,6,7,6};
    //int n = sizeof(carnes)/sizeof(carnes[0]);
    //cout<<n<<endl;
    int peso=15, k = 4;
    //k = 4 => maxima diferencia de peso
    //cada trozo tiene un peso ti
    vector<vector<int>> ordenes;
    while (true) {
        vector<int>unaOrden;
        vector<int>indices;
        if (construir_orden(0,peso,carnes,k,unaOrden,indices)) {
            ordenes.push_back(unaOrden);
            //esta iterativa es para recorrer el arreglo de las carnes y borrar donde se guardaron los indices
            for (int i=indices.size()-1;i>=0;i--) {
                //cout<<*carnes.begin()<<" + "<<indices[i]<<endl;
                carnes.erase(carnes.begin()+indices[i]);
            }
        }else {
            break;
        }
    }
    for (auto laOrden: ordenes) {
        for (int i=0;i<laOrden.size();i++) {
            cout<<laOrden[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
