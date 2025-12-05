#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* fila_criar() {

    Fila* f = (Fila*)malloc(sizeof(Fila));

    // Se a alocação funcionou (f não é NULL)
    if (f) {
        f->inicio = NULL;   // A fila começa sem ninguém
        f->fim = NULL;      // A fila termina sem ninguém
        f->tamanho = 0;     // Contador zerado
    }
    return f;
}

void fila_destruir(Fila* f) {
    if (!f) return; // Se a fila não existe, não faz nada

    NoFila* atual = f->inicio;

    // Percorre toda a fila liberando nó por nó
    while (atual != NULL) {
        NoFila* temp = atual;       // Guarda o nó atual para apagar depois
        atual = atual->proximo;     // Avança para o próximo antes de apagar
        free(temp);                 // Libera a memória do nó
    }

    free(f);
}

void fila_enqueue(Fila* f, void* dados) {
    if (!f) return;

    // Cria um novo nó para carregar os dados
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    novo->dados = dados;
    novo->proximo = NULL; // já que é o último, não aponta para ninguém

    // Verifica se a fila estava vazia
    if (f->fim == NULL) {
        // Se estava vazia, o novo elemento é tanto o início quanto o fim
        f->inicio = novo;
    } else {
        // Se já tinha gente, o antigo último agora aponta para o novo
        f->fim->proximo = novo;
    }

    // Atualiza o ponteiro de fim para ser o novo nó
    f->fim = novo;
    f->tamanho++;
}

void* fila_dequeue(Fila* f) {
    // Verifica se a fila existe ou se está vazia
    if (!f || f->inicio == NULL) return NULL;

    // Pega o nó que está na ponta da fila
    NoFila* temp = f->inicio;
    void* dados = temp->dados; // Salva o conteúdo (Jogador/Monstro) para retornar depois

    // Avança o início da fila para o segundo da lista
    f->inicio = f->inicio->proximo;

    // Se a fila ficou vazia após a remoção
    if (f->inicio == NULL) {
        f->fim = NULL; // O fim também deve ser NULL
    }

    free(temp);
    f->tamanho--;

    return dados; // Indica quem é a vez no sistema de combate
}

int fila_vazia(Fila* f) {
    return (f == NULL || f->tamanho == 0);
}
