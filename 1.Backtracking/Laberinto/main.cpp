#include <iostream>

using namespace std;

//filas
#define ROWS 10
//columnas
#define COLS 10

int direcciones[4][2]={
    {-1,0},
    {0,1},
    {1,0},
    {0,-1}
};

void imprimir_laberinto(char maze[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl<<endl;
}

bool validar_posicion(int r,int c,char maze[ROWS][COLS],bool visitado[ROWS][COLS]) {
    return (r>=0 && r<ROWS && c>=0 && c<COLS &&
        maze[r][c]!='#' and !visitado[r][c]);
}


bool solucion(int x,int y,char maze[ROWS][COLS],bool visitado[ROWS][COLS]) {
    if (maze[x][y] == 'E') {return true;}
    visitado[x][y] = true;//posicion inicial
    for (int i = 0; i < 4; i++) {//esto es debido a la cantidad de movimientos
        int new_x = x + direcciones[i][0];
        int new_y = y + direcciones[i][1];
        if (validar_posicion(new_x, new_y,maze,visitado)) {
            if (solucion(new_x, new_y,maze,visitado)) {
                if (maze[x][y]!='S') {
                    maze[x][y]='.';
                }

                return true;
            }
        }

    }
}


int main() {
    // Legend:
    // 'S': Start
    // ' ': Path
    // '#': Wall
    // 'E': Exit

    char maze[ROWS][COLS] = {
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

    bool visitado[ROWS][COLS] = {false};
    // for (int i = 0; i < ROWS; i++) {
    //     for (int j = 0; j < COLS; j++) {
    //         cout << visitado[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout<<"Laberinto inicial: "<<endl;
    imprimir_laberinto(maze);
    cout<<"Solucion: "<<endl;
    solucion(0,0,maze,visitado);
    imprimir_laberinto(maze);
    return 0;
}
