
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // tamanho fixo da fila

// Estrutura da peça
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// Estrutura da fila
typedef struct {
    Peca pecas[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

// Funções da fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->qtd = 0;
}

// Gera uma peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma peça no final da fila
void enqueue(Fila *f, Peca p) {
    if (f->qtd == TAM_FILA) {
        printf("Fila cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    f->fim = (f->fim + 1) % TAM_FILA;
    f->pecas[f->fim] = p;
    f->qtd++;
}

// Remove a peça da frente da fila
void dequeue(Fila *f) {
    if (f->qtd == 0) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = f->pecas[f->inicio];
    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (f->qtd == 0) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila de peças:\n");
    int i;
    int idx = f->inicio;
    for (i = 0; i < f->qtd; i++) {
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int contadorID = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorID++));
    }

    int opcao;
    do {
        printf("\n--- TETRIS STACK ---\n");
        exibirFila(&fila);
        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Adicionar nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(contadorID++));
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
