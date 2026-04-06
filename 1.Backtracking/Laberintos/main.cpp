#include <iostream>

using namespace std;

#define FILA 10

#define COLUMNA 10

void imprimir(bool visitado[FILA][COLUMNA]) {
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {
            cout << visitado[i][j] << " ";
        }
        cout << endl;
    }
}

//cambio el orden de las direcciones -> una ruta diferente
int direcciones[4][2] = {
    {-1 , 0},
    { 0 , 1},
    { 1 , 0},
    { 0 , -1}
};

void imprimir_Maze(char maze[FILA][COLUMNA]) {
    for (int i = 0; i < FILA; i++) {
        for (int j = 0; j < COLUMNA; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

bool validar(int nuevo_x,int nuevo_y,char maze[FILA][COLUMNA],bool visitado[FILA][COLUMNA]) {
    return (nuevo_x>=0 and nuevo_x< FILA and nuevo_y>=0 and nuevo_y<=COLUMNA and
        maze[nuevo_x][nuevo_y] != '#' and !visitado[nuevo_x][nuevo_y]);
}

bool solucion(int x,int y,char maze[FILA][COLUMNA],bool visitado[FILA][COLUMNA]) {
    //conficion de parada
    //si llegamos al E => entonces llegamos al fin del laberinto
    if (maze[x][y]=='E') {
        return true;
    }
    //estoy en esta casilla
    visitado[x][y]=true;
    //itera hasta 4 por la cantidad de movimientos
    for (int i = 0; i < 4; i++) {
        //indicamos el nuevo movimiento
        int nuevo_x = x + direcciones[i][0];
        int nuevo_y = y + direcciones[i][1];
        //validamos que sea el correcto
        //le enviamos el nuevo movimiento que puede ser izq, derecha ,arriba o abajo
        //pasa que como nos hemos movido para la derecha, digamos que en la nueva pos nos queremos mover para la izq
        //aqui es donde entra el visitado[x][y] = true , pues al momento de validar verá que ya hemos estado en esa posición
        if (validar(nuevo_x,nuevo_y,maze,visitado)) {
            if (solucion(nuevo_x,nuevo_y,maze,visitado)) {
                //Sin esta condición, la posición de inicio sería marcada como parte del camino
                if (maze[x][y]!='S') {
                    //donde me encuentro es diferente de 'S'
                    maze[x][y]='.';
                    //entonces marco el camino
                }
                return true;
            }
        }
    }

    return false;
}


//problema del laberinto

int main() {
    //dibujamos el laberinto
    char maze[FILA][COLUMNA] = {
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
    //S : START
    //' ' : CAMINO
    //'#'   : WALL
    //'E'   : Exit
    bool visitado[FILA][COLUMNA] = {false};
    //se crea una matriz con puros falsos
    //imprimir(visitado);
    cout<<"Maze initial state"<<endl;
    imprimir_Maze(maze);
    cout<<"Imprimir solucion"<<endl;
    solucion(0,0,maze,visitado);
    imprimir_Maze(maze);
    return 0;
}
