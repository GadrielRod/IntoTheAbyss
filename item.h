#ifndef ITEM_H
#define ITEM_H

typedef enum {
    ITEM_ARMA,
    ITEM_ARMADURA,
    ITEM_POCAO,
    ITEM_ALIADO,
    ITEM_ESPECIAL
} TipoItem;

// NOVO ENUM: Define qual status o item melhora
typedef enum {
    STATUS_DANO,    // Aumenta o dano causado
    STATUS_DEFESA,  // Aumenta a defesa (bloqueio)
    STATUS_ATAQUE,  // Aumenta o acerto (2d6 + x)
    STATUS_HP,      // Aumenta a Vida Máxima
    STATUS_NENHUM   // Para itens sem bonus passivo
} TipoStatus;

typedef struct {
    char nome[50];
    char descricao[100];
    TipoItem tipo;
    TipoStatus status_afetado; // NOVO CAMPO
    int valor;
    int id_carta;
} Item;

// Função atualizada para receber o status
Item* item_criar(const char* nome, TipoItem tipo, TipoStatus status, int valor, const char* desc);
void item_liberar(void* dados);

#endif
