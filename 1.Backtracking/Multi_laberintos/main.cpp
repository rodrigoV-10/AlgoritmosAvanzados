#include <iostream>

#define FILAS 10
#define COLUMNAS 10

using namespace std;

int direcciones[4][2] = {
    {1,0},
    {-1,0},
    {0,-1},
    {0,1}
};

void imprimir_laberintos(char maze[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
}

bool validar(int nx,int ny,char maze[FILAS][COLUMNAS],bool visitado[FILAS][COLUMNAS]) {
    return nx>=0 && nx<FILAS && ny>=0 && ny<COLUMNAS && maze[nx][ny]!='#' and !visitado[nx][ny];
}
//recordar que como todo esta en false <- matriz booleana
//verifico que se mantenga en false pues !false <- true :)

void solucion(int x,int y,char maze[FILAS][COLUMNAS],bool visitado[FILAS][COLUMNAS]) {
    if (maze[x][y]=='E') {
        imprimir_laberintos(maze);
        return;
    }
    char old_value = maze[x][y];
    maze[x][y]='.';
    visitado[x][y]=true;
    for (int i=0;i<4;i++) {
        //nuevos movimientos
        int nx=x+direcciones[i][0];
        int ny=y+direcciones[i][1];
        if (validar(nx,ny,maze,visitado)) {
            solucion(nx,ny,maze,visitado);

        }
    }
    //lo que hace es que a todo el camino lo vuelvo a marcar con su valor antiguo
    //y vuelvo a completarlo con ceros
    maze[x][y]=old_value;
    visitado[x][y]=false;
}

int main() {

    //creamos una matriz de visitado
    bool visitado[FILAS][COLUMNAS]{};

    char maze[FILAS][COLUMNAS] = {
        {'S', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', ' ', 'E'}
    };

    //imprimir_laberintos(maze);
    cout<<"Solucion"<<endl;
    solucion(0,0,maze,visitado);


    return 0;
}
