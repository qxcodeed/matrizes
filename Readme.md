## Atividades Possíveis para fazer em sala.

- Mudar o queimada para ver o retorno da recursão de outra cor.
- Construir os metodos de vizinhos e de embaralhamento.
- Preencher uma imagem recursivamente aleatoriamente.
- Preencher uma imagem recursivamente aleatoriamente mostrando o nivel da recursao.
- Fazer o floodfill para preencher uma imagem.
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

### Atividade 1

Você deve implmentar a criação do labirinto utilizando recursão.

	funcao furar(posicao, matriz):
		se posicao esta fora da matriz:
			return
		se posicao eh furavel:
			fure
			chame furar aleatoriamente para todos os vizinhos

### Atividade 2

Você deve implementar o algoritmo que gera um labirinto utilizando pilha.
Vale uma pontuação especial se conseguir implementar sem as quinas.

    funcao gerar_lab(matriz, pilha):
		furar primeira posicao
		empilhar a primeira posicao
		enquanto pilha nao estiver vazia:
		  pegar vizinhos do topo
		  selecionar os vizinhos que sao furaveis
		  se existirem vizinhos furaveis:
			escolha um
			fure
			empilhe
		  senão:
			desempilhe

### Atividade 3

Você deve implementar a solução do labirinto utilizando pilha.
