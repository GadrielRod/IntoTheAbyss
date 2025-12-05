#ifndef ENTIDADE_H
#define ENTIDADE_H

typedef enum {
    CLASSE_GUERREIRO,
    CLASSE_NECROMANTE,
    CLASSE_SACERDOTE,
    CLASSE_HUNTERS,
    CLASSE_MONSTRO
} TipoClasse;

typedef struct {
    char nome[50];
    TipoClasse classe;
    int nivel;      // Nível para definir quantos ataques por rodada a entidade pode fazer
    int hp_atual;   // Vida atual da classe
    int hp_max;     // Vida máxima da classe
    int ataque;     // Bônus para acertar (2d6 + ataque)
    int defesa;     // Classe de Armadura
    int dano_base;  // Dano fixo causado ao acertar
    int buff_dano;  // Dano temporário (Poção de Fúria)
    char acao_descricao[100];
} Entidade;

// Função atualizada
Entidade* entidade_criar(const char* nome, TipoClasse classe, int hp, int atk, int def, int dano, int nivel);
void entidade_liberar(void* dados);
int rolar_dados(); // simula a rolagem usando o rand de 2d6
void entidade_imprimir_status(Entidade* e);

#endif
