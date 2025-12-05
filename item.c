#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

// Atualizado com TipoStatus
Item* item_criar(const char* nome, TipoItem tipo, TipoStatus status, int valor, const char* desc) {
    Item* i = (Item*)malloc(sizeof(Item));
    strncpy(i->nome, nome, 49);
    strncpy(i->descricao, desc, 99);
    i->tipo = tipo;
    i->status_afetado = status; // Salva o tipo de bônus
    i->valor = valor;
    i->id_carta = 0;
    return i;
}

void item_liberar(void* dados) {
    free(dados);
}
