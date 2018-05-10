/*

  Esse arquivo contém as seguintes classes e funções.
  Par - Define um par linha e coluna, bem como suas operações
  matriz - Define uma classe template para matrizes
  matchar - funções para entrada e saída de matrizes de caracteres
  MatrizView - Classe para desenho de Matrizes

*/

#include <vector>
#include <iostream>

using namespace std;

using Pos = sf::Vector2i;

template<class T>
using matriz = vector<vector<T>>;

namespace ed{
    float LADO = 20;
}


#ifndef MATRIZVIEW
#define MATRIZVIEW
#include <SFML/Graphics.hpp>
#include "ed_base.h"


class MatrizView{
public:
    struct Offset{
        int left;
        int right;
        int up;
        int down;
    };
    Offset off;
private:

    MyPlayer * my_player;
    sf::RenderTexture * my_painel;
    int larg{1};//largura da linha

    MatrizView()
    {
        off.up = 30;
        off.left = 0;
        off.right = 0;
        off.down = 30;
        my_player = MyPlayer::instance();
        my_painel = MyPlayer::getPainel();

        my_player->color_back = (sf::Color(216,216,255));
        my_player->color_front = (sf::Color::Black);
        off.up = my_player->offset_up;
    }

public:

    static MatrizView * instance(){
        static MatrizView smview;
        return &smview;
    }

    //permite ao usuario desenhar uma matriz. Salva o desenho em mat
    void paint_brush(matriz<char> &mat, const string &colors){
        MyWindow::instance()->setVisible(true);
        char cor_atual = colors[0];
        bool isDown = false;
        bool acabou = false;
        sf::Vector2i lastPos;

        MyColors * cm = MyColors::instance();
        //sf::Color back = player->get_color_back();
        while(!acabou){
            sf::Event event;
            while(MyWindow::instance()->pollEvent(event)){
                MyWindow::instance()->processar_resize(event);
                if(MyWindow::instance()->processar_close(event))
                    acabou = true;
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Return)
                        acabou = true;
                    else{
                        char c = cm->sf2char(event.key.code);
                        if(colors.find(c) != string::npos)
                            if(cm->exists(c))
                                cor_atual = c;
                    }
                }
                if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        isDown = true;
                        lastPos = pixel2mat(sf::Mouse::getPosition(*MyWindow::instance()));
                    }

                }
                if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left)
                        isDown = false;
                }
            }

            //processar cliques no mouse de pinturas
            //if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(isDown){
                sf::Vector2i newPos = pixel2mat(sf::Mouse::getPosition(*MyWindow::instance()));
                auto path = MyPathMaker::make_path(sf::Vector2f(lastPos), sf::Vector2f(newPos));
                for(auto pmat : path)
                    if(mat_is_inside(mat, sf::Vector2i(pmat.x, pmat.y)))
                        mat[pmat.y][pmat.x] = cor_atual;
                lastPos = newPos;
            }

            MyWindow::instance()->clear(my_player->color_back);
            string texto = string() + "Digite " + colors + " para trocar de Cor " +
                    "ou Enter para terminar!";
            MyWindow::instance()->draw(sfText(sf::Vector2f(off.left, 0), texto, my_player->color_front));
            paint_target_squares(*MyWindow::instance(), mat);
            MyWindow::instance()->display();
        }
    }


    //mostra um texto e retorna um ponto clicado para o usuario
    Pos select_point(const matriz<char>& mat, const string & texto){
        MyWindow::instance()->setVisible(true);
        sf::Vector2u square;
        bool acabou = false;
        square.x = 0;
        square.y = 0;
        while(!acabou){
            sf::Event event;
            while(MyWindow::instance()->pollEvent(event)){
                MyWindow::instance()->processar_resize(event);
                if(MyWindow::instance()->processar_close(event))
                    acabou = true;
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Q)
                        acabou = true;
                }
                else if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        int px = event.mouseButton.x;
                        int py = event.mouseButton.y;
                        sf::Vector2i mouse(px, py);

                        auto pmat = pixel2mat(mouse);
                        if(mat_is_inside(mat, pmat)){
                            square = sf::Vector2u(pmat.x, pmat.y);
                            acabou = true;
                        }
                    }
                }
            }

            MyWindow::instance()->clear(my_player->color_back);
            MyWindow::instance()->draw(sfText(sf::Vector2f(off.left, 0), texto,
                                              my_player->color_front));
            paint_target_squares(*MyWindow::instance(), mat);
            MyWindow::instance()->display();
        }
        return Pos(square.x, square.y);
    }

    sf::Vector2f get_paint_pos(const Pos &pos){
        float side = ed::LADO;
        return sf::Vector2f(larg + off.left + pos.x * side, larg + off.up + pos.y * side);
    }

    //desenha a matriz no rendertarget usando o mapa de cores
    void paint_target_squares(sf::RenderTarget &rt, const matriz<char> &mat){
        sf::RectangleShape rect;
        float side = ed::LADO;
        rect.setSize(sf::Vector2f(side - larg, side - larg));
        for(int c = 0; c < (int) mat[0].size(); c++){
            for(int l = 0; l < (int) mat.size(); l++){
                rect.setFillColor(my_colors->get(mat[l][c]));
                rect.setPosition(get_paint_pos(Pos(c, l)));
                rt.draw(rect);
            }
        }
    }

    //desenha a matriz no rendertarget usando o mapa de cores
    void paint_target_cell(const Pos &pos, char color){
//        Par size = buffer_size_mat;
//        sf::RectangleShape rect;
//        float side = recalc_side(*my_painel, size);
//        rect.setSize(sf::Vector2f(side - larg, side - larg));
//        rect.setFillColor(MyColors::instance()->get(color));
//        rect.setPosition(get_paint_pos(*my_painel, pos, size));
//        my_painel->draw(rect);
        sf::CircleShape circ;
        circ.setRadius((ed::LADO - larg)/2);
        //circ.setSize(sf::Vector2f(side - larg, side - larg));
        sf::Color cor = MyColors::instance()->get(color);
        //cor.a = 150;
        circ.setFillColor(cor);
        circ.setPosition(get_paint_pos(pos));
        my_painel->draw(circ);
    }

    //desenha as tags
    void paint_target_tags(sf::RenderTarget &rt, const matriz<string>& mtag){
        sfText text;
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color::Black);
        for(int c = 0; c < (int) mtag[0].size(); c++){
            for(int l = 0; l < (int) mtag.size(); l++){
                string str = mtag[l][c];
                text.setString(str);
                if(str.size() == 1)
                    text.setCharacterSize(0.8 * ed::LADO);
                else if(str.size() == 2)
                    text.setCharacterSize(0.65 * ed::LADO);
                else if(str.size() == 3)
                    text.setCharacterSize(0.5 * ed::LADO);
                else
                    text.setCharacterSize(0.36 * ed::LADO);
                text.setPosition(get_paint_pos(Pos(c, l)));
                rt.draw(text);
            }
        }
    }

private:
    sf::Vector2i pixel2mat(const sf::Vector2i &pos){
        int y = (pos.y - off.up) / ed::LADO;
        int x = (pos.x - off.left) / ed::LADO;
        return sf::Vector2i(x, y);
    }

    template <class T>
    bool mat_is_inside(matriz<T> mat, Pos pos){
        int nl = mat.size();
        int nc = mat[0].size();
        if(pos.x < 0 || pos.x >= nc)
            return false;
        if(pos.y < 0 || pos.y >= nl)
            return false;
        return true;
    }
    template <class T>
    sf::Vector2i mat_size(const matriz<T>& mat){
        return sf::Vector2i(mat.size(), mat[0].size());
    }
};

//FUNCOES SOBRE MATRIZES


namespace ed {
//Faz uma pintura livre tal qual o paint brush
//sobre a matriz passada por parametro. A variavel
//colors define quais cores poderão ser utilizadas
//na pintura.
void mat_paint(matriz<char>& mat, const string& colors){
    MatrizView::instance()->paint_brush(mat, colors);
}

//Mostra o texto e espera o usuario clicar em uma posição
//valida na matriz
Pos mat_click(const matriz<char>& mat, const string & texto){
    return MatrizView::instance()->select_point(mat, texto);
}

void mat_show(const matriz<char>& mchar, const vector<Pos>& focus = {}, const string cores = "",
              const matriz<string>& mtag = matriz<string>()){

    MatrizView::instance()->paint_target_squares(*MyPlayer::getPainel(), mchar);
    for(int i = 0; i < (int) focus.size(); i++){
        Pos pos = focus[i];
        char color = cores[i];
        MatrizView::instance()->paint_target_cell(pos, color);
    }
    if(mtag.size() > 0)
        MatrizView::instance()->paint_target_tags(*MyPlayer::getPainel(), mtag);
    MyPlayer::instance()->push();
}

}

#endif // MATRIZVIEW


