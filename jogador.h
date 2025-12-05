#ifndef JOGADOR_H
#define JOGADOR_H

#include "entidade.h"
#include "lista.h"
#include "item.h"

typedef struct {
    Entidade* base;         // Status base (HP, Classe)
    char nome_jogador[50];

    Lista* inventario;      // Lista de itens coletados

    // Equipamentos Atuais (Ponteiros para itens dentro do inventário)
    Item* arma_equipada;
    Item* armadura_equipada;
    Item* aliado_equipado;

    int coringas_encontrados; // Precisa de 2 para o Boss
    int cartas_compradas;     // Ranking (score)
} Jogador;

// --- Funções de Criação e Destruição ---
Jogador* jogador_criar(const char* nome, TipoClasse classe_escolhida);
void jogador_destruir(Jogador* j);

// --- Gestão de Inventário ---
void jogador_adicionar_item(Jogador* j, Item* i);
void jogador_equipar_item(Jogador* j, Item* i);
void jogador_usar_pocao(Jogador* j, Item* i);

// --- Cálculos de Status (Protótipos que faltavam) ---
int jogador_calcular_hp_max_total(Jogador* j); // <--- ESTE ERA O QUE FALTAVA
int jogador_calcular_dano_total(Jogador* j);
int jogador_calcular_ataque_total(Jogador* j);
int jogador_calcular_defesa_total(Jogador* j);

#endif
