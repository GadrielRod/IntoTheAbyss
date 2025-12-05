#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* pilha_criar() {
    return lista_criar(); // Reutiliza Lista
}

void pilha_destruir(Pilha* p, void (*free_dados)(void*)) {
    lista_destruir(p, free_dados);
}

void pilha_push(Pilha* p, void* dados) {
    lista_inserir(p, dados);
}

void* pilha_pop(Pilha* p) {
    if (!p || p->tamanho == 0) return NULL;
    // Remove o primeiro elemento (topo)
    // Como lista_remover precisa do ponteiro do dado, usamos um truque:
    // pegamos o dado do topo e mandamos remover.
    void* dados = p->cabeca->dados;
    return lista_remover(p, dados);
}

int pilha_tamanho(Pilha* p) {
    return lista_tamanho(p);
}

// Algoritmo de Fisher-Yates para embaralhar a lista encadeada
void pilha_embaralhar(Pilha* p) {
    if (!p || p->tamanho < 2) return;

    int n = p->tamanho;
    void** array_temp = (void**)malloc(n * sizeof(void*));

    // 1. Copia tudo para um array temporário
    NoLista* atual = p->cabeca;
    for (int i = 0; i < n; i++) {
        array_temp[i] = atual->dados;
        atual = atual->proximo;
    }

    // 2. Embaralha o array
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        void* temp = array_temp[i];
        array_temp[i] = array_temp[j];
        array_temp[j] = temp;
    }

    // 3. Devolve para a lista na nova ordem
    atual = p->cabeca;
    for (int i = 0; i < n; i++) {
        atual->dados = array_temp[i];
        atual = atual->proximo;
    }

    free(array_temp);
}
