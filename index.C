#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de Email
typedef struct Email {
    char titulo[100];
    char mensagem[500];
    int urgencia; // Quanto maior, mais urgente
} Email;

// Nó da fila
typedef struct No {
    Email email;
    struct No* proximo;
} No;

// Fila de prioridade
typedef struct {
    No* inicio;
} Fila;

// Inicializar a fila
void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
}

// Criar um novo email
Email criarEmail(const char* titulo, const char* mensagem, int urgencia) {
    Email email;
    strncpy(email.titulo, titulo, sizeof(email.titulo));
    strncpy(email.mensagem, mensagem, sizeof(email.mensagem));
    email.urgencia = urgencia;
    return email;
}

// Inserir email na fila com base na prioridade
void inserirEmail(Fila* fila, Email email) {
    No* novo = (No*)malloc(sizeof(No));
    novo->email = email;
    novo->proximo = NULL;

    if (fila->inicio == NULL || email.urgencia > fila->inicio->email.urgencia) {
        novo->proximo = fila->inicio;
        fila->inicio = novo;
    } else {
        No* atual = fila->inicio;
        while (atual->proximo != NULL && atual->proximo->email.urgencia >= email.urgencia) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
}

// Remover o email mais prioritário
Email removerEmail(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        exit(EXIT_FAILURE);
    }
    No* temp = fila->inicio;
    Email email = temp->email;
    fila->inicio = fila->inicio->proximo;
    free(temp);
    return email;
}

// Mostrar todos os emails da fila
void mostrarFila(Fila* fila) {
    No* atual = fila->inicio;
    printf("Fila de Emails:\n");
    while (atual != NULL) {
        printf("Título: %s | Urgência: %d\n", atual->email.titulo, atual->email.urgencia);
        atual = atual->proximo;
    }
    printf("\n");
}
int main() {
    Fila fila;
    inicializarFila(&fila);

    inserirEmail(&fila, criarEmail("Trabalho de faculdade", "Entregar projeto até amanhã", 8));
    inserirEmail(&fila, criarEmail("Promoção", "Descontos em eletrônicos", 3));
    inserirEmail(&fila, criarEmail("Reunião urgente", "Reunião com o chefe às 10h", 10));
    inserirEmail(&fila, criarEmail("Amigo", "Vamos sair no fim de semana?", 2));

    mostrarFila(&fila);

    printf("Removendo email mais urgente...\n");
    Email emailRemovido = removerEmail(&fila);
    printf("Removido: %s\n\n", emailRemovido.titulo);

    mostrarFila(&fila);

    return 0;
}