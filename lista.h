#ifndef LISTA_H
#define LISTA_H

// Nó genérico para a lista encadeada
typedef struct NoLista {
    void* dados;
    struct NoLista* proximo;
} NoLista;

// O TAD Lista
typedef struct {
    NoLista* cabeca;
    int tamanho;
} Lista;

// --- Funções ---
Lista* lista_criar();
void lista_destruir(Lista* l, void (*free_dados)(void*));
void lista_inserir(Lista* l, void* dados); // Insere no início
void* lista_remover(Lista* l, void* dados); // Remove um item específico
void* lista_buscar_indice(Lista* l, int indice); // Retorna o dado no índice X
int lista_tamanho(Lista* l);

#endif
