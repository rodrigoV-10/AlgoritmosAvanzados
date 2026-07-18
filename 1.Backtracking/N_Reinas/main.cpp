#include <iostream>

#define N 4

using namespace  std;

void inicializar_tablero(char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '*';
        }
    }
}

void print_board(char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j];
        }
        cout<<endl;
    }
}

bool validar(int cur_col,int cur_row,char board[N][N]) {
    for (int i = cur_col ; i>=0 ; i--) {
        if (board[cur_row][i]=='Q') {
            return false;
        }
    }

    for (int i = cur_row , j= cur_col ; i>=0 && j>=0  ; i--, j--) {
        if (board[i][j]== 'Q') {
            return false;
        }
    }

    for (int i=cur_row, j=cur_col; i<N && j>=0 ; i++ , j--) {
        if (board[i][j]== 'Q') {
            return false;
        }
    }

    return true;

}

//columna = column
//fila = row
void proceso_solucion(int cur_col,char board[N][N]) {
    //cuando llegamos a la última columna salimos de la recursividad pues ya colocamos todas las reinas
    if (cur_col==N) {
        cout<<"Solucion proceso"<<endl;
        print_board(board);
        return;
    }
    //recorremos todas las filas de cada columna
    for (int row = 0; row < N; row++) {
        if (validar(cur_col,row,board)) {
            //si la posición es válida entonces coloco la reina
            board[row][cur_col]='Q';
            proceso_solucion(cur_col+1,board);
            //y aumento la pos de la columna
            board[row][cur_col]='*';
            //si al camino no funciona , coloco un " * "
        }
    }
}

int main() {
    cout << "holaaaaaaa :) "<<endl;
    cout << "Hemos vuelto :) "<<endl;
    //problam de backtracking -> puedo mezclar iterativas con recursividad, además de que
    //puedo avanzar y si avanzo tmbn tengo que retroceder :)

    //problema de las N_reinas

    char board[N][N];
    //inicializamos el tablero
    inicializar_tablero(board);
    //imprimirmos el tablero
    //print_board(board);
    //le envio la posición inicial
    proceso_solucion(0,board);

    return 0;
}
