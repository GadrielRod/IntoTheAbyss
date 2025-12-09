/*
 * JOGADOR.C
 * Gerencia status e cálculos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"

Jogador* jogador_criar(const char* nome, TipoClasse classe_escolhida) {
    Jogador* j = (Jogador*)malloc(sizeof(Jogador));
    strncpy(j->nome_jogador, nome, 49);
    j->inventario = lista_criar();
    j->arma_equipada = NULL;
    j->armadura_equipada = NULL;
    j->aliado_equipado = NULL;
    j->coringas_encontrados = 0;
    j->cartas_compradas = 0;

    // --- VALORES BASE ---
    int hp, atk, def, dano;
    switch (classe_escolhida) {
        case CLASSE_GUERREIRO:  hp = 24; atk = 4; def = 11; dano = 6; break;
        case CLASSE_NECROMANTE: hp = 18; atk = 3; def = 10; dano = 15; break;
        case CLASSE_SACERDOTE:  hp = 36; atk = 3; def = 10; dano = 4; break;
        case CLASSE_HUNTERS:    hp = 21; atk = 4; def = 11;  dano = 5; break;
    }

    j->base = entidade_criar(nome, classe_escolhida, hp, atk, def, dano, 1);
    return j;
}
// Função destrutora: Evita Memory Leaks 
void jogador_destruir(Jogador* j) {
    if (!j) return;
    entidade_liberar(j->base);
    lista_destruir(j->inventario, item_liberar);
    free(j);
}

void jogador_adicionar_item(Jogador* j, Item* i) {
    lista_inserir(j->inventario, i);
    printf(">> Item obtido: %s (%s)\n", i->nome, i->descricao);
}

void jogador_equipar_item(Jogador* j, Item* i) {
    if (i->tipo == ITEM_ARMA) {
        j->arma_equipada = i;
        printf(">> Voce equipou a arma: %s\n", i->nome);
    } else if (i->tipo == ITEM_ARMADURA) {
        j->armadura_equipada = i;
        printf(">> Voce equipou a armadura: %s\n", i->nome);
    } else if (i->tipo == ITEM_ALIADO) {
        j->aliado_equipado = i;
        printf(">> %s agora esta te ajudando!\n", i->nome);
    }
}

void jogador_usar_pocao(Jogador* j, Item* i) {
    if (i->tipo != ITEM_POCAO) return;
    
    if (strstr(i->nome, "Furia") != NULL) {
        printf(">> Voce bebeu a POCAO DE FURIA! (+3 Dano neste combate)\n");
        j->base->buff_dano += 3;
    } else {
        printf(">> Voce bebeu a POCAO DE VIDA! (+10 HP)\n");
        j->base->hp_atual += 10; 
        // Verifica se passou do Max HP calculado
        int max_hp = jogador_calcular_hp_max_total(j);
        if (j->base->hp_atual > max_hp) 
            j->base->hp_atual = max_hp;
    }
    
    lista_remover(j->inventario, i);
    item_liberar(i);
}

// --- CÁLCULOS DINÂMICOS ---

int jogador_calcular_hp_max_total(Jogador* j) {
    int total = j->base->hp_max;
    // Soma itens que dão HP
    if (j->arma_equipada && j->arma_equipada->status_afetado == STATUS_HP)
        total += j->arma_equipada->valor;
    if (j->armadura_equipada && j->armadura_equipada->status_afetado == STATUS_HP)
        total += j->armadura_equipada->valor;
    return total;
}

int jogador_calcular_dano_total(Jogador* j) {
    int total = j->base->dano_base;
    
    // Soma itens que dão Dano
    if (j->arma_equipada && j->arma_equipada->status_afetado == STATUS_DANO)
        total += j->arma_equipada->valor;
    if (j->armadura_equipada && j->armadura_equipada->status_afetado == STATUS_DANO)
        total += j->armadura_equipada->valor;
        
    // Aliado Guerreiro
    if (j->aliado_equipado && strstr(j->aliado_equipado->nome, "Guerreiro"))
        total += 3;

    total += j->base->buff_dano;
    return total;
}

int jogador_calcular_ataque_total(Jogador* j) {
    int total = j->base->ataque;
    
    // Soma itens que dão Ataque (Acerto)
    if (j->arma_equipada && j->arma_equipada->status_afetado == STATUS_ATAQUE)
        total += j->arma_equipada->valor;
    if (j->armadura_equipada && j->armadura_equipada->status_afetado == STATUS_ATAQUE)
        total += j->armadura_equipada->valor;
        
    // Aliado Caçador
    if (j->aliado_equipado && strstr(j->aliado_equipado->nome, "Caçador"))
        total += 3;
        
    return total;
}

int jogador_calcular_defesa_total(Jogador* j) {
    int total = j->base->defesa;
    
    // Soma itens que dão Defesa
    if (j->arma_equipada && j->arma_equipada->status_afetado == STATUS_DEFESA)
        total += j->arma_equipada->valor;
    if (j->armadura_equipada && j->armadura_equipada->status_afetado == STATUS_DEFESA)
        total += j->armadura_equipada->valor;
        
    return total;
}
