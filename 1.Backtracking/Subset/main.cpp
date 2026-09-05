#include <iostream>
#include <vector>

using namespace std;

void backtrack(int indice,vector<int>&numeros,
    vector<vector<int>>&soluciones,vector<int>&actual) {
    if (indice==numeros.size()) {
        soluciones.push_back(actual);
        return;
    }
    //tomar
    //guardamos la primera solucion
    actual.push_back(numeros[indice]);
    //backtrack
    backtrack(indice+1,numeros,soluciones,actual);
    //deshacer el cambio
    actual.pop_back();
    //no tomar
    //como ya se deshizo el cambio , avanzamos al siguiente indice sin agregar
    backtrack(indice+1,numeros,soluciones,actual);
}

void backtrackIterativo(int i,vector<int>&numeros,
    vector<vector<int>>&soluciones,vector<int>&actual) {
    if (i==numeros.size()) {
        soluciones.push_back(actual);
        return;
    }
    for (int j=0; j<numeros.size(); j++) {
        actual.push_back(numeros[j]);
        backtrackIterativo(i+1,numeros,soluciones,actual);
        actual.pop_back();
    }
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
    //calcular todos los subconjuntos posibles :)
    vector<int>numeros = {1,2,3};
    vector<vector<int>> soluciones;
    vector<int>actual;
    cout<<"DE MANERA RECURSIVA"<<endl;
    backtrack(0,numeros,soluciones,actual);
    for (auto&subconjunto : soluciones) {
        for (int i=0; i<subconjunto.size(); i++) {
            cout << subconjunto[i] << " ";
        }
        cout << endl;
    }
    cout<<endl<<endl;
    cout<<"======================="<<endl;
    cout<<"DE MANERA ITERATIVA"<<endl;
    backtrackIterativo(0,numeros,soluciones,actual);
    for (auto&subconjunto : soluciones) {
        for (int i=0; i<subconjunto.size(); i++) {
            cout << subconjunto[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
