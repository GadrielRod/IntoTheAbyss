#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entidade.h"

Entidade* entidade_criar(const char* nome, TipoClasse classe, int hp, int atk, int def, int dano, int nivel) {
    Entidade* e = (Entidade*)malloc(sizeof(Entidade));
    strncpy(e->nome, nome, 49);
    e->classe = classe;
    e->hp_max = hp;
    e->hp_atual = hp;
    e->ataque = atk;
    e->defesa = def;
    e->dano_base = dano; // Novo campo
    e->buff_dano = 0;    // Começa zerado
    e->nivel = nivel;
    strcpy(e->acao_descricao, "ataca");
    return e;
}

void entidade_liberar(void* dados) {
    free(dados);
}

int rolar_dados() {
    return (rand() % 6 + 1) + (rand() % 6 + 1); // 2d6
}

void entidade_imprimir_status(Entidade* e) {
    printf("[%s] HP: %d/%d | ATK: +%d | DEF: %d | DANO: %d\n",
        e->nome, e->hp_atual, e->hp_max, e->ataque, e->defesa, e->dano_base);
}
