/*
 * BARALHO.C
 * Responsável por criar o deck e definir os atributos dos itens/monstros
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"

Carta* criar_carta_vazia(Naipe n, ValorCarta v) {
    Carta* c = (Carta*)malloc(sizeof(Carta));
    c->naipe = n;
    c->valor = v;
    c->monstro_associado = NULL;
    c->item_associado = NULL;
    c->tipo_efeito = EFEITO_EVENTO_LORE;
    return c;
}

void configurar_carta_numerica(Carta* c) {
    c->tipo_efeito = EFEITO_MONSTRO;

    // MONSTROS NIVEL 1 (HP, ATK, DEF, DANO)
    // Goblin: 10, 3, 10, 3
    // Soldado: 14, 3, 11, 4
    // Cultista: 12, 4, 10, 4
    // Aranha: 13, 4, 9, 5

    // MONSTROS NIVEL 2 (HP, ATK, DEF, DANO)
    // Demonio: 22, 6, 12, 6
    // Servo: 20, 5, 13, 6
    // Amalgama: 26, 4, 11, 7
    // Aberracao: 24, 5, 10, 8

    // Espadas/Paus = Foco em combate
    if (c->naipe == ESPADAS) {
        switch(c->valor) {
            case VALOR_2:
                c->monstro_associado = entidade_criar("Goblin", CLASSE_MONSTRO, 10, 2, 10, 3, 1); break;
            case VALOR_3:
                c->monstro_associado = entidade_criar("Goblin Reanimado", CLASSE_MONSTRO, 12, 4, 9, 3, 1); break;
            case VALOR_4: case VALOR_5:
                c->monstro_associado = entidade_criar("Soldado Reanimado", CLASSE_MONSTRO, 14, 3, 11, 4, 1); break;
            case VALOR_6:
                c->monstro_associado = entidade_criar("Líder do Culto", CLASSE_MONSTRO, 16, 3, 10, 3, 2); break;
            case VALOR_7:
                c->monstro_associado = entidade_criar("Aranha Gigante", CLASSE_MONSTRO, 13, 4, 9, 5, 1); break;
            case VALOR_8:
                c->monstro_associado = entidade_criar("Demonio da Escuridao", CLASSE_MONSTRO, 20, 5, 12, 6, 2); break;
            case VALOR_9:
                c->monstro_associado = entidade_criar("Servo Leal do Lich", CLASSE_MONSTRO, 24, 6, 13, 6, 2); break;
            case VALOR_10:
                c->monstro_associado = entidade_criar("Amalgama Viva", CLASSE_MONSTRO, 24, 4, 10, 7, 2); break;
            default: break;
        }
    }
    else if (c->naipe == PAUS) {
        switch(c->valor) {
            case VALOR_2: c->monstro_associado = entidade_criar("Goblin", CLASSE_MONSTRO, 10, 2, 10, 3, 1); break;
            case VALOR_3: case VALOR_4: c->monstro_associado = entidade_criar("Cultista", CLASSE_MONSTRO, 13, 2, 9, 3, 1); break;
            case VALOR_5: c->monstro_associado = entidade_criar("Aranha Gigante", CLASSE_MONSTRO, 13, 4, 9, 5, 1); break;
            case VALOR_6: c->monstro_associado = entidade_criar("Soldado Reanimado", CLASSE_MONSTRO, 14, 3, 11, 4, 1); break;
            case VALOR_7: c->monstro_associado = entidade_criar("Demonio da Escuridao", CLASSE_MONSTRO, 20, 5, 12, 6, 2); break;
            case VALOR_8: c->monstro_associado = entidade_criar("Aberracao", CLASSE_MONSTRO, 26, 4, 11, 8, 2); break;
            case VALOR_9: c->monstro_associado = entidade_criar("Servo Leal do Lich", CLASSE_MONSTRO, 24, 6, 13, 6, 2); break;
            case VALOR_10: c->tipo_efeito = EFEITO_EVENTO_DANO;
                strcat(c->nome_carta, " (Armadilha de Espinhos) "); break;
            default: break;
        }
    }
    else if (c->naipe == OUROS) {
        switch(c->valor) {
            case VALOR_2: c->monstro_associado = entidade_criar("Cultista", CLASSE_MONSTRO, 13, 2, 9, 3, 1); break;
            case VALOR_3: case VALOR_8: c->tipo_efeito = EFEITO_EVENTO_OURO; strcat(c->nome_carta, " (Ouro Perdido) "); break;
            case VALOR_4: c->monstro_associado = entidade_criar("Soldado Reanimado", CLASSE_MONSTRO, 14, 3, 11, 4, 1); break;
            case VALOR_5: case VALOR_9: c->tipo_efeito = EFEITO_EVENTO_DANO; strcat(c->nome_carta, " (Armadilha Oculta) "); break;
            case VALOR_6: c->monstro_associado = entidade_criar("Demonio da Escuridao", CLASSE_MONSTRO, 20, 5, 12, 6, 2); break;
            case VALOR_7: c->tipo_efeito = EFEITO_EVENTO_GATO; strcat(c->nome_carta, " (Gato Preto) "); break;
            case VALOR_10: c->monstro_associado = entidade_criar("Amalgama Viva", CLASSE_MONSTRO, 24, 4, 10, 7, 2); break;
            default: break;
        }
    }
    else if (c->naipe == COPAS) {
         if(c->valor == 7) {
             c->monstro_associado = entidade_criar("Aberracao", CLASSE_MONSTRO, 26, 4, 11, 8, 2);
         } else if (c->valor >= 8) {
             c->tipo_efeito = EFEITO_EVENTO_LORE;
             c->id_evento = c->valor - 7;
             strcat(c->nome_carta, " (Memórias do Abismo) ");
         } else if (c->valor == 5) {
             c->tipo_efeito = EFEITO_EVENTO_PIADA;
             strcat(c->nome_carta, " (Figura Estranha) ");
         } else if (c->valor == 6){
             c->tipo_efeito = EFEITO_EVENTO_PIADA_2;
             strcat(c->nome_carta, " (Vulto Misterioso) ");
         }else {
             c->tipo_efeito = EFEITO_EVENTO_CURA;
             strcat(c->nome_carta, " (Espirito Protetor) ");
         }
    }
}

Pilha* baralho_criar_dungeon(TipoClasse classe_jogador) {
    Pilha* baralho = pilha_criar();

    for (int n = 0; n < 4; n++) {
        // 1. Cartas Numéricas
        for (int v = 2; v <= 10; v++) {
            Carta* c = criar_carta_vazia((Naipe)n, (ValorCarta)v);
            sprintf(c->nome_carta, "%d de %s", v, n==ESPADAS?"Espadas":n==PAUS?"Paus":n==OUROS?"Ouros":"Copas");
            configurar_carta_numerica(c);
            pilha_push(baralho, c);
        }

        // 2. Valetes (J) = Poções
        Carta* cJ = criar_carta_vazia((Naipe)n, VALOR_J);
        cJ->tipo_efeito = EFEITO_ITEM;

        if (n == COPAS || n == OUROS) {
            sprintf(cJ->nome_carta, "Valete de %s (Pocao Vida)", n==OUROS?"Ouros":"Copas");
            cJ->item_associado = item_criar("Pocao de Vida", ITEM_POCAO, STATUS_HP, 10, "Cura 10 de Vida");
        } else {
            sprintf(cJ->nome_carta, "Valete de %s (Pocao Furia)", n==ESPADAS?"Espadas":"Paus");
            cJ->item_associado = item_criar("Pocao de Furia", ITEM_POCAO, STATUS_DANO, 3, "+3 Dano Temporario");
        }
        pilha_push(baralho, cJ);

        // 3. Damas (Q) = Armas (Status Variáveis por Naipe)
        Carta* cQ = criar_carta_vazia((Naipe)n, VALOR_Q);
        cQ->tipo_efeito = EFEITO_ITEM;

        char nome_arma[50];
        char desc_arma[100];
        TipoStatus stat_arma;
        int valor_arma = 3 + (n % 2); // 2 ou 3

        if (n == ESPADAS) { // DANO
            sprintf(nome_arma, "Espada Grande");
            sprintf(desc_arma, "Concede +%d de DANO", valor_arma);
            stat_arma = STATUS_DANO;
        } else if (n == PAUS) { // DEFESA
            sprintf(nome_arma, "Machado de Batalha");
            sprintf(desc_arma, "Concede +%d de DEFESA", valor_arma);
            stat_arma = STATUS_DEFESA;
        } else if (n == OUROS) { // HP
            sprintf(nome_arma, "Lança Vampirica");
            sprintf(desc_arma, "Concede +%d de HP MAX", valor_arma * 3);
            valor_arma *= 3;
            stat_arma = STATUS_HP;
        } else { // ATAQUE (Copas)
            sprintf(nome_arma, "Adaga Refinada");
            sprintf(desc_arma, "Concede +%d de ATAQUE (Acerto)", valor_arma);
            stat_arma = STATUS_ATAQUE;
        }

        sprintf(cQ->nome_carta, "Dama de %s (%s)", n==ESPADAS?"Espadas":n==PAUS?"Paus":n==OUROS?"Ouros":"Copas", nome_arma);
        cQ->item_associado = item_criar(nome_arma, ITEM_ARMA, stat_arma, valor_arma, desc_arma);
        pilha_push(baralho, cQ);

        // 4. Reis (K) = Armaduras (Status Variáveis por Naipe)
        Carta* cK = criar_carta_vazia((Naipe)n, VALOR_K);
        cK->tipo_efeito = EFEITO_ITEM;

        char nome_armor[50];
        char desc_armor[100];
        TipoStatus stat_armor;
        int valor_armor = 3 + (n % 2);

        if (n == ESPADAS) { // DANO
            sprintf(nome_armor, "Armadura de Espinhos");
            sprintf(desc_armor, "Concede +%d de DANO", valor_armor);
            stat_armor = STATUS_DANO;
        } else if (n == PAUS) { // DEFESA
            sprintf(nome_armor, "Armadura Reforçada");
            sprintf(desc_armor, "Concede +%d de DEFESA", valor_armor);
            stat_armor = STATUS_DEFESA;
        } else if (n == OUROS) { // HP
            sprintf(nome_armor, "Armadura Arcana");
            sprintf(desc_armor, "Concede +%d de HP MAX", valor_armor * 3);
            valor_armor *= 3;
            stat_armor = STATUS_HP;
        } else { // ATAQUE
            sprintf(nome_armor, "Couro Leve");
            sprintf(desc_armor, "Concede +%d de ATAQUE (Acerto)", valor_armor);
            stat_armor = STATUS_ATAQUE;
        }

        sprintf(cK->nome_carta, "Rei de %s (%s)", n==ESPADAS?"Espadas":n==PAUS?"Paus":n==OUROS?"Ouros":"Copas", nome_armor);
        cK->item_associado = item_criar(nome_armor, ITEM_ARMADURA, stat_armor, valor_armor, desc_armor);
        pilha_push(baralho, cK);

        // 5. Ases (A) = Aliados
        if ((int)classe_jogador != n) {
            Carta* cA = criar_carta_vazia((Naipe)n, VALOR_A);
            cA->tipo_efeito = EFEITO_ITEM;

            char nome_aliado[50];
            char desc_aliado[100];
            TipoStatus stat_aliado = STATUS_NENHUM;

            switch(n) {
                case CLASSE_GUERREIRO:
                    strcpy(nome_aliado, "Aliado Guerreiro");
                    strcpy(desc_aliado, "+3 de Dano passivo");
                    stat_aliado = STATUS_DANO;
                    break;
                case CLASSE_NECROMANTE:
                    strcpy(nome_aliado, "Aliado Necromante");
                    strcpy(desc_aliado, "Drena 3 HP do inimigo por turno");
                    break;
                case CLASSE_SACERDOTE:
                    strcpy(nome_aliado, "Aliado Sacerdote");
                    strcpy(desc_aliado, "Cura 5 HP por turno");
                    break;
                case CLASSE_HUNTERS:
                    strcpy(nome_aliado, "Aliado Caçadores");
                    strcpy(desc_aliado, "+3 de Ataque passivo");
                    stat_aliado = STATUS_ATAQUE;
                    break;
            }

            sprintf(cA->nome_carta, "As de %s (%s)", n==ESPADAS?"Espadas":n==PAUS?"Paus":n==OUROS?"Ouros":"Copas", nome_aliado);
            cA->item_associado = item_criar(nome_aliado, ITEM_ALIADO, stat_aliado, 2, desc_aliado);
            pilha_push(baralho, cA);
        }
    }

    // 6. Coringas
    for(int i=0; i<2; i++) {
        Carta* c = criar_carta_vazia(CORINGA_NAIPE, VALOR_CORINGA_VAL);
        strcpy(c->nome_carta, "CORINGA - FILACTERIO DO LICH");
        c->tipo_efeito = EFEITO_BOSS_KEY;
        pilha_push(baralho, c);
    }

    return baralho;
}

void carta_liberar(void* dados) {
    Carta* c = (Carta*)dados;
    if (c->monstro_associado) entidade_liberar(c->monstro_associado);
    if (c->item_associado) item_liberar(c->item_associado);
    free(c);
}
