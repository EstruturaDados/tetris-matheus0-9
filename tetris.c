#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura que representa uma peça do jogo
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Variável global para gerar IDs únicos
int proximoId = 0;

// Função para gerar uma peça automaticamente
Peca gerarPeca() {
    Peca novaPeca;

    char tipos[] = {'I', 'O', 'T', 'L'};
    novaPeca.nome = tipos[rand() % 4];

    novaPeca.id = proximoId++;

    return novaPeca;
}

// Inicializa a fila
void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

// Insere uma peça no final da fila (enqueue)
void enqueue(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("\nA fila está cheia! Não é possível adicionar nova peça.\n");
        return;
    }

    fila->itens[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
}

// Remove uma peça da frente da fila (dequeue)
Peca dequeue(Fila *fila) {
    Peca removida = {' ', -1};

    if (filaVazia(fila)) {
        printf("\nA fila está vazia!\n");
        return removida;
    }

    removida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;

    return removida;
}

// Exibe o estado atual da fila
void exibirFila(Fila *fila) {
    printf("\nFila de peças:\n");

    if (filaVazia(fila)) {
        printf("[Vazia]\n");
        return;
    }

    int posicao = fila->inicio;

    for (int i = 0; i < fila->quantidade; i++) {
        printf("[%c %d] ", fila->itens[posicao].nome,
                          fila->itens[posicao].id);

        posicao = (posicao + 1) % TAM_FILA;
    }

    printf("\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        exibirFila(&fila);

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca removida = dequeue(&fila);

                if (removida.id != -1) {
                    printf("\nPeça jogada: [%c %d]\n",
                           removida.nome,
                           removida.id);
                }
                break;
            }

            case 2:
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);

                    printf("\nNova peça adicionada: [%c %d]\n",
                           nova.nome,
                           nova.id);
                } else {
                    printf("\nA fila já está cheia!\n");
                }
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

