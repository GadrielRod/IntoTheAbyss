#ifndef BARALHO_H
#define BARALHO_H

#include "pilha.h"
#include "entidade.h"
#include "item.h"

// Naipes e Valores do Baralho
typedef enum { ESPADAS, PAUS, OUROS, COPAS, CORINGA_NAIPE } Naipe;
typedef enum {
    VALOR_2 = 2, VALOR_3, VALOR_4, VALOR_5, VALOR_6,
    VALOR_7, VALOR_8, VALOR_9, VALOR_10,
    VALOR_J = 11, // Valete (Poção)
    VALOR_Q = 12, // Dama (Arma)
    VALOR_K = 13, // Rei (Armadura)
    VALOR_A = 14, // Ás (Aliado/Classe)
    VALOR_CORINGA_VAL = 0 // Especial
} ValorCarta;

// O que esta carta faz quando comprada?
typedef enum {
    EFEITO_MONSTRO,         // Inicia combate
    EFEITO_ITEM,            // Item melhora atributo
    EFEITO_EVENTO_LORE,     // Contar a história
    EFEITO_EVENTO_CURA,     // Cura o jogador
    EFEITO_EVENTO_DANO,     // Armadilha
    EFEITO_EVENTO_OURO,     // Narrativo
    EFEITO_EVENTO_GATO,     // Narrativo
    EFEITO_EVENTO_PIADA,    // Narrativo
    EFEITO_EVENTO_PIADA_2,  // Narrativo
    EFEITO_BOSS_KEY         // Coringa
} TipoEfeito;

// Estrutura da Carta
typedef struct {
    Naipe naipe;
    ValorCarta valor;
    char nome_carta[50]; // Ex: "Ás de Espadas"

    TipoEfeito tipo_efeito;

    // Dados associados (apenas um destes será usado dependendo do efeito)
    Entidade* monstro_associado; // Se for monstro (cria na hora de processar)
    Item* item_associado;        // Se for item
    int id_evento;               // ID para lore/piada
} Carta;

// --- Funções ---
// Cria o baralho completo (54 cartas), removendo a classe que o jogador escolheu
Pilha* baralho_criar_dungeon(TipoClasse classe_jogador);

// Processa o efeito da carta (cria o monstro, dá o item, mostra o texto)
void carta_processar_efeito(Carta* c, void* estado_jogo);

// Libera a memória da carta
void carta_liberar(void* dados);

#endif
