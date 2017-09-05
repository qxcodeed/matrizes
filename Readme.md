
## Link das Atividades

[![](https://qxcodeed.github.io/pages/matrizes/figura.png)](https://qxcodeed.github.io/pages/matrizes.html)

## Tipo Par
- Métodos e Atributos

```c++
struct Par{
    int l, c;// linha e coluna

    //cria um par passando linha e coluna
    Par(int l = 0, int c = 0);

    //retorna um novo par a partir da soma de dois pares
    Par operator+(const Par& other);

    //compara dois pares
    bool operator ==(const Par& other);
};
```

- Exemplo de uso:

```c++
Par p(5, 7);
cout << p.l; //5
cout << p.c; //7
Par x = Par(1, 0) + Par(2, 0); //x = Par(3, 0)
cout << (Par(1, 1) == (Par(1, 1)); //true

```

---
## Classe Matriz
- Métodos e atributos públicos

```c++
template<class T> 
class matriz{
    //cria matriz vazia
    matriz();

    //cria matriz a partir de outra
    matriz(const matriz& mat);

    //cria matriz passando num de linhas colunas e valor default
    matriz(int nl, int nc, T init);

    //obtem um elemento da matriz com para leitura e escrita
    T& get(int l, int c);

    //retorna o numero de linhas
    int sizeL();

    //retorna o numero de colunas
    int sizeC();

    //retorna um par com o numero de linhas e colunas
    Par size();

    //retorna true se o ponto estiver dentro da matriz
    bool is_inside(int l, int c);

    //sobrecarga do get para Par
    T& get(const Par& p);

    //sobrecarga do is_inside usando par
    bool is_inside(const Par& p);

    //retorna true se o par está na matriz e possui esse valor
    bool equals(const Par& pos, const T& value);

    //retorna todas as posições da matriz
    vector<Par> posicoes();
};
```

- Exemplo de Uso.

```c++
//cria uma matriz de char de 10 linhas, 20 colunas
//com todos os elementos sendo o char y
matriz<char> matc(10, 20, 'y'); 

matriz<char> mat2(matc);//cria mat2 copiando matc

matc.get(0, 0) = 'k';//pega o elemento (0, 0) e põe k na posição

cout << matc.sizeL(); //10

cout << matc.isInside(Par(-1, 0)); //false

cout << matc.equals(Par(1, 1), 'y'); //true
```

## Pintando

```c++
//includes
#include "libs/ed_base.h"
#include "libs/ed_mat.h"

//main
int nlin = 30;
int ncol = 60;

matchar<char> matc(nlin, ncol, 'k');//matriz preta
matchar<int>  mati(nlin, ncol,   0);//matriz de zeros

mat_draw(matc);//desenha a matriz de cores
mat_focus(Par(3, 3), 'c');//faz uma bolinha ciano na posicao (3, 3)
mat_draw(mati); //escreve os números
ed_show(); //mostra na tela

//observe que se voce fizer os numero antes das cores, as cores vao cobrir os numeros.

//pinte os numeros se precisar. Marque os estados com bolinhas se precisar.

ed_lock();//antes de terminar a main para evitar fechamento abrupto do player
```