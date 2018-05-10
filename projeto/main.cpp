#include "libs/ed_base.h"
#include "libs/ed_mat.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

int nlinhas = 20;
int ncolunas = 35;

//MAPA DE CORES
//r red
//g green
//b blue
//m magenta
//c cyan -
//y yellow
//w white
//k black

template <class T>
matriz<T> mat_create(int nl, int nc, T value){
    return vector<vector<T>>(nl, vector<T>(nc, value));
}

template<class T>
bool mat_is_inside(matriz<T> mat, Pos pos){
    int nl = mat.size();
    int nc = mat[0].size();
    if((pos.x < 0) || (pos.x >= nc))
        return false;
    if((pos.y < 0) || (pos.y >= nl))
        return false;
    return true;
}

void queimar(matriz<char> &mat, Pos pos){
    //PONTOS DE PARADA
    int l = pos.y;
    int c = pos.x;
    if(!mat_is_inside(mat, pos))//se estiver fora da matriz
        return;
    if(mat[l][c] != 'g')//se nao for arvore
        return;

    //DESENHO
    ed::mat_show(mat, {pos}, "c");
    mat[l][c] = 'r';

    //RECURSAO
    queimar(mat, Pos(c + 1, l    ));//down
    queimar(mat, Pos(c - 1, l    ));//up
    queimar(mat, Pos(c    , l + 1));//right
    queimar(mat, Pos(c    , l - 1));//left

    //ACAO APOS A RECURSAO
    mat[l][c] = 'k';

    //DESENHO
    ed::mat_show(mat, {pos}, "c");
}


int main(){
    int nl = 20;
    int nc = 40;

    ed::LARGURA = 960;
    ed::ALTURA = 660;
    ed::BUFFER_SIZE = 100;
    ed::LADO = ed::LARGURA / nc;

    matriz<char> mat = mat_create(nl, nc, 'g');

    //chama o metodo de desenho livre onde a cor primeira default eh branca
    ed::mat_paint(mat, "wg");
    Pos pos = ed::mat_click(mat, "escolha uma arvore para queimar");
    queimar(mat, pos);//chama a função recursiva
    ed::lock();//impede que termine abruptamente

    return 0;
}


