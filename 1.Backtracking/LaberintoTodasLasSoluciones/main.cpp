#include <iostream>

using namespace std;

#define ROWS  10
#define  COLS 10

int directions [4][2] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

void print_maze(char maze[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

bool is_valid(int r, int c, char maze[ROWS][COLS], bool visited[ROWS][COLS]) {
    //valido que la fila o columna se encuentre en el rango
    //valido que no sea una pared
    //como todo el mapa de booleanos esta en false, entonces su negación es verdadero, caso contrario
    //si es que fuese verdadero ya no cumple la lógica
    return (r >= 0 && r < ROWS && c >= 0 && c < COLS &&
            maze[r][c] != '#' && !visited[r][c]);
}

void solve(int x, int y, char maze[ROWS][COLS], bool visited[ROWS][COLS]) {
    if (maze[x][y] == 'E') {
        cout << "New Solution Found!" << endl;
        print_maze(maze);
        return;
    }
    //usando esto me aseguro de marcar la posicion desde donde inicie el recorrido en el laberinto
    // visited[x][y] = true;
    // if (maze[x][y] != 'E') {
    //     maze[x][y] = '.';
    // }
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        if (is_valid(new_x, new_y, maze, visited)) {
            //con esto no marco la posicion inicial de donde parto en el mapa
            visited[new_x][new_y] = true;
            if (maze[new_x][new_y] != 'E') {
                maze[new_x][new_y] = '.';
            }
            solve(new_x, new_y, maze, visited);
            visited[new_x][new_y] = false;
            if (maze[new_x][new_y] != 'E') {
                maze[new_x][new_y] = ' ';
            }
        }
    }

    // visited[x][y] = false;
    // if (maze[x][y] != 'E') {
    //     maze[x][y] = ' ';
    // }
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

    bool visited[ROWS][COLS] = {false};
    cout << "Maze initial state" << endl;
    print_maze(maze);

    solve(0, 0, maze, visited);
    // print_maze(maze);
    return 0;
}