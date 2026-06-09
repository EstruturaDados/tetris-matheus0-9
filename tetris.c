#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura da peça
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

// Estrutura da pilha
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Variável global para IDs únicos
int proximoId = 0;

// Gera uma peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = proximoId++;

    return nova;
}

// ==================== FILA ====================

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

void enqueue(Fila *fila, Peca peca) {
    if (filaCheia(fila))
        return;

    fila->itens[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
}

Peca dequeue(Fila *fila) {
    Peca removida = {' ', -1};

    if (filaVazia(fila))
        return removida;

    removida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;

    return removida;
}

// ==================== PILHA ====================

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

void push(Pilha *pilha, Peca peca) {
    if (pilhaCheia(pilha))
        return;

    pilha->topo++;
    pilha->itens[pilha->topo] = peca;
}

Peca pop(Pilha *pilha) {
    Peca removida = {' ', -1};

    if (pilhaVazia(pilha))
        return removida;

    removida = pilha->itens[pilha->topo];
    pilha->topo--;

    return removida;
}

// ==================== EXIBIÇÃO ====================

void exibirEstado(Fila *fila, Pilha *pilha) {
    int pos;

    printf("\n=====================================\n");
    printf("Estado Atual:\n\n");

    printf("Fila de Pecas:\n");
    pos = fila->inicio;

    for (int i = 0; i < fila->quantidade; i++) {
        printf("[%c %d] ",
               fila->itens[pos].nome,
               fila->itens[pos].id);

        pos = (pos + 1) % TAM_FILA;
    }

    printf("\n\n");

    printf("Pilha de Reserva (Topo -> Base):\n");

    if (pilhaVazia(pilha)) {
        printf("[Vazia]");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ",
                   pilha->itens[i].nome,
                   pilha->itens[i].id);
        }
    }

    printf("\n=====================================\n");
}

// ==================== MAIN ====================

int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {

        exibirEstado(&fila, &pilha);

        printf("\n1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca jogada = dequeue(&fila);

                printf("\nPeca jogada: [%c %d]\n",
                       jogada.nome,
                       jogada.id);

                // Mantém a fila cheia
                enqueue(&fila, gerarPeca());

                break;
            }

            case 2: {

                if (pilhaCheia(&pilha)) {
                    printf("\nPilha de reserva cheia!\n");
                } else {

                    Peca reservada = dequeue(&fila);

                    push(&pilha, reservada);

                    printf("\nPeca reservada: [%c %d]\n",
                           reservada.nome,
                           reservada.id);

                    // Mantém a fila cheia
                    enqueue(&fila, gerarPeca());
                }

                break;
            }

            case 3: {

                if (pilhaVazia(&pilha)) {
                    printf("\nNao ha pecas reservadas!\n");
                } else {

                    Peca usada = pop(&pilha);

                    printf("\nPeca reservada utilizada: [%c %d]\n",
                           usada.nome,
                           usada.id);
                }

                break;
            }

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}