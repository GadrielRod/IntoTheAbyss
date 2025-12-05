#ifndef PILHA_H
#define PILHA_H

#include "lista.h"

// A Pilha reutiliza a estrutura da Lista
typedef Lista Pilha;

// --- Funções ---
Pilha* pilha_criar();
void pilha_destruir(Pilha* p, void (*free_dados)(void*));
void pilha_push(Pilha* p, void* dados); // Empilha (põe no topo)
void* pilha_pop(Pilha* p);              // Desempilha (tira do topo)
int pilha_tamanho(Pilha* p);
void pilha_embaralhar(Pilha* p);        // Função especial para "baralhar" a pilha

#endif
