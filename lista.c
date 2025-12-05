#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

 // Cria o "cabeçalho" da lista, que gerencia o primeiro elemento e o tamanho.
Lista* lista_criar() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    if (l) {
        l->cabeca = NULL; // Lista começa vazia
        l->tamanho = 0;
    }
    return l;
}


 //Limpa toda a memória da lista.
void lista_destruir(Lista* l, void (*free_dados)(void*)) {
    if (!l) return;

    NoLista* atual = l->cabeca;
    while (atual != NULL) {
        NoLista* temp = atual;
        atual = atual->proximo; // Salva o próximo antes de destruir o atual

        // Se a função de limpeza foi fornecida, limpa o dado interno
        if (free_dados && temp->dados) {
            free_dados(temp->dados);
        }
        free(temp); // Libera o nó
    }
    free(l); // Libera a estrutura de controle
}

//Adiciona um elemento no início (cabeça) da lista
void lista_inserir(Lista* l, void* dados) {
    if (!l) return;

    NoLista* novo = (NoLista*)malloc(sizeof(NoLista));
    novo->dados = dados;

    novo->proximo = l->cabeca; // O novo nó aponta para onde o início (cabeça) apontava

    // A cabeça agora é o novo nó
    l->cabeca = novo;
    l->tamanho++;
}

//Procura um ponteiro de dados específico e o remove da lista.
void* lista_remover(Lista* l, void* dados) {
    if (!l || !l->cabeca) return NULL;

    NoLista* atual = l->cabeca;
    NoLista* ant = NULL; // Rastrea o anterior para recosturar a lista

    // Procura o dado percorrendo a lista
    while (atual != NULL && atual->dados != dados) {
        ant = atual;
        atual = atual->proximo;
    }

    if (!atual) return NULL; // Caso chegou no fim e não achou o item

    // Se o item estava no início (cabeça)
    if (!ant) {
        l->cabeca = atual->proximo;
    }
    // Se estava no meio ou fim
    else {
        ant->proximo = atual->proximo; //Pula o nó atual
    }

    void* ret = atual->dados; // Guarda o dado para retornar
    free(atual);             // Libera só o nó
    l->tamanho--;

    return ret;
}

 // Acessa a lista como se fosse um vetor
 // Usado no menu de inventário para selecionar o item "1", "2", etc.
void* lista_buscar_indice(Lista* l, int indice) {
    if (!l || indice < 0 || indice >= l->tamanho) return NULL;

    NoLista* atual = l->cabeca;
    // Caminha N vezes até chegar no índice desejado
    for (int i = 0; i < indice; i++) {
        atual = atual->proximo;
    }
    return atual->dados;
}

int lista_tamanho(Lista* l) {
    return l ? l->tamanho : 0;
}
