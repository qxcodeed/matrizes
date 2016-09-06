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

void queimar(matchar &mat, Par par){
    //PONTOS DE PARADA
    if(!mat.is_inside(par))//se estiver fora da matriz
        return;
    if(mat.get(par) != 'g')//se nao for arvore
        return;

    //ACAO
    mat.get(par) = 'r';

    //DESENHO
    mat_draw(mat);//desenha a matriz
    mat_focus(par, 'c');//faz uma bolinha em par
    ed_show();//mostra na tela

    //RECURSAO
    queimar(mat, Par(par.l + 1, par.c    ));//down
    queimar(mat, Par(par.l - 1, par.c    ));//up
    queimar(mat, Par(par.l    , par.c + 1));//right
    queimar(mat, Par(par.l    , par.c - 1));//left

    //ACAO APOS A RECURSAO
    mat.get(par) = 'k';

    //DESENHO
    mat_draw(mat);//desenha a matriz
    mat_focus(par, 'c');//faz uma bolinha em par
    ed_show();//mostra na tela
}


int main(){

    //cria uma matriz de caracteres de 15 linhas por 20 colunas, e preenche todos os elementos
    //com 'y'
    matchar mat(15, 20, 'g');

    //chama o metodo de desenho livre onde a cor primeira default eh branca
    mat_paint_brush(mat, "wg");

    Par par = mat_get_click(mat, "escolha uma arvore para queimar");

    queimar(mat, par);//chama a função recursiva

    ed_lock();//impede que termine abruptamente

    return 0;
}


