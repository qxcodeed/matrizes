## Atividades Possíveis para fazer em sala.

- Mudar o queimada para ver o retorno da recursão de outra cor.
- Construir os metodos de vizinhos e de embaralhamento.
- Preencher uma imagem recursivamente aleatoriamente.
- Preencher uma imagem recursivamente aleatoriamente mostrando o nivel da recursao.
- Fazer o floodfill para preenche uma imagem.
- Usar o floodfill para encontrar o menor caminho entre dois pontos.
- Construir o labirinto usando pilha.
- Construir o labirinto recursivamente.
- Resolver o labirinto usando pilha.
- Resolver o labirinto recursivamente.
- Transformar um labirinto perfeito em arvore.
- Transformar uma árvore em labirinto perfeito.
- Fazer uma busca em árvore para gerar uma IA que jogue o jogo da velha.

## Funções Auxiliares

Crie uma funcao auxiliar que recebe um ponto e retorna os vizinhos desse ponto

    //vizinhos nas 4 direcoes Left, Up, Right, Down
    vector<Pos> gerar_vizinhos(Pos pos);

    //vizinhos nas 8 direções
    vector<Pos> gerar_todos_vizinhos(Pos pos);

Crie uma função auxiliar que embaralha um vetor de posicoes

    void embaralhar(vector<Pos> vet);

## Atividades com labirinto.

### Resolver um labirinto perfeito.

Na pasta de inputs existem arquivos de texto que contém labirintos perfeitos.
Você deve ler o labirinto de entrada in e gerar o labirinto resolvido out.

No arquivo de entrada você tem:

    l c
    matrix
    li ci
    lf cf

    l e c são o tamanho linha e coluna da matriz, seguido pela própria matriz.
    Os valores li e ci são linha e coluna do ponto de inicio do labirinto.
    Os valores lf e cf são linha e coluna do ponto de fim do labirinto.

O arquivo inputs/pmaze_10_10_in.txt possui:

    10 10
    ##########
    #  ##    #
    ## #  ## #
    ## # ##  #
    #  #  ####
    ## ##    #
    #   ### ##
    ### ##   #
    #      # #
    ##########
    1 1
    4 1

A resposta para esse labirinto está no inputs/p_maze_10_10_out.txt

    10 10
    ##########
    #..##    #
    ##.#  ## #
    ##.# ##  #
    #..#  ####
    ## ##    #
    #   ### ##
    ### ##   #
    #      # #
    ##########

Os ... são o caminho a ser percorrido entre os dois pontos.

## Trabalho 1

Você deve implementar tanto a solução de pilha para encontrar a saída do labirinto.
Na pasta input você encontrará outros exemplos de entrada e saída.

## Trabalho 2

Você deve implementar o algoritmo que gera um labirinto utilizando pilha.
Vale uma pontuação especial se conseguir implementar sem as quinas.
