#include "Funciones/Utils.hpp"

bool validar(int carne,int diferencia,vector<int>unaOrden) {
    if (unaOrden.empty()) {
        return true;
    }
    for (int carne_nueva: unaOrden) {
        if (abs(carne - carne_nueva) <= diferencia) {
            return true;
        }
    }
    return false;
}

bool solucion_backtracking(int i,vector<int>&pedazos,int diferencia,
    int peso,vector<int>&unaOrden,vector<bool>&usados) {
    if (peso==0) {
        return true;
    }
    for (int idx=i; idx<pedazos.size(); idx++) {
        int carne = pedazos[idx];
        if (!usados[idx] && carne<=peso &&validar(carne,diferencia,unaOrden)) {
            unaOrden.push_back(carne);
            usados[idx] = true;
            if (solucion_backtracking(idx+1,pedazos,diferencia,peso-carne,unaOrden,usados)) {
                return true;
            }
            unaOrden.pop_back();
            usados[idx] = false;
        }
    }
    return false;
}


int main() {
    vector<int> pedazos{2,8,9,6,7,6};
    int diferencia=4;
    int peso=15;
    vector<vector<int>> ordenes;
    vector<bool>usados(pedazos.size(),false);
    while (true) {
        vector<int> unaOrden;
        if(solucion_backtracking(0,pedazos,diferencia,peso,unaOrden,usados)) {
            ordenes.push_back(unaOrden);
        }else {
            break;
        }
    }
    for (auto &unaOrden: ordenes) {
        for (int carne: unaOrden) {
            cout << carne << " ";
        }
        cout << endl;
    }
    return 0;
}
