/*
 * MAIN.C - ARQUIVO PRINCIPAL
 * Projeto: Into the Abyss
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> 

#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "entidade.h"
#include "item.h"
#include "jogador.h"
#include "baralho.h"

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

int ler_input_seguro() {
    char buffer[100];
    char *fim_ptr;
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 0) continue;
            long valor = strtol(buffer, &fim_ptr, 10);
            if (*fim_ptr == '\0') return (int)valor;
        }
        printf(" >> Entrada invalida! Digite um NUMERO: ");
    }
}

void imprimir_lore(int id_evento, TipoClasse classe) {
    printf("\n=== MEMORIA DO ABISMO ===\n");
    if (id_evento == 1) {
        switch(classe) {
            case CLASSE_GUERREIRO: printf("\"Voce limpa o sangue da espada e seu reflexo no aço manchado o encara. \nVoce se pergunta se Eldraine o reconheceria assim, coberto pela sujeira do Abismo.\"\n"); break;
            case CLASSE_NECROMANTE: printf("\"Voce passa por um tumulo improvisado. \nA imagem de sua mae, palida e doente, invade sua mente. \n'O poder de Aldous é profano... mas se for o preço para ve-la de novo?'\"\n"); break;
            case CLASSE_SACERDOTE: printf("\"Vislumbres do simbolo de Aerion partido ao meio vem a sua mente. \nVoce sente o peso da fe... e o medo de que Eda sofra o mesmo destino.\"\n"); break;
            case CLASSE_HUNTERS: printf("\"Wolf solta um ganido baixo. Voce o acalma, mas o cheiro de morte no ar o lembra do porque estão nessa. \nVoce tenta imaginar o cheiro do mar. \n'So mais um pouco...', voce sussurra.\"\n"); break;
            default: break;
        }
    }
    else if (id_evento == 2) {
        switch(classe) {
            case CLASSE_GUERREIRO: printf("\"Seu braco doi. Voce ve as veias escurecendo sob a pele, um eco da corrupcao de Aldous que destruiu seus ancestrais. Voce nao esta apenas lutando contra um Lich; esta lutando contra o destino de sua linhagem.\"\n"); break;
            case CLASSE_NECROMANTE: printf("\"Ao tocar nas escrituras do seu tomo antigo, um sussurro gelido preenche sua mente. 'Eles tambem a deixaram morrer...' A voz nao e sua. Voce recua, assustada. A proximidade com o poder do Lich esta... chamando.\"\n"); break;
            case CLASSE_SACERDOTE: printf("\"Voce sente a presenca de Lyssandra neste lugar. A visao de Aerion retorna: 'Sua necromancia pode ser a porta. Nao deixe que ela seja aberta.'\"\n"); break;
            case CLASSE_HUNTERS: printf("\"Wolf comeca a tremer. A corrupcao do Abismo o esta afetando. Voce escuta sons distantes. Se voce nao se cuidar, talvez tenha que escolher entre seu amigo e sua propria vida.\"\n"); break;
            default: break;
        }
    }
    else if (id_evento == 3) {
        switch(classe) {
            case CLASSE_GUERREIRO: printf("\"'Nao importa', voce pensa. 'Eu nao volto como um soldado pedindo. Eu volto como o heroi que ela merece.'\"\n"); break;
            case CLASSE_NECROMANTE: printf("\"Aldous está proximo. Voce sente a vibraçao do poder. Voce ve sua mae sorrindo, saudavel. Seria uma ilusao? Ou uma promessa? Voce percebe que nao se importa mais. Voce vai descobrir o segredo, custe o que custar.\"\n"); break;
            case CLASSE_SACERDOTE: printf("\"A luz de Aerion mal penetra aqui. A fe e sua unica armadura. Voce se lembra do juramento: purificar o Abismo. Nao ha mais duvida. Aldous deve cair, ou Eda caira com você.\"\n"); break;
            case CLASSE_HUNTERS: printf("\"Voce sente uma brisa semelhante ao mar passar por voce. O contraste parece brutal. Esta nao e mais uma caçada por dinheiro. Voce tem que sair daqui para sentir o sol nascer sobre suas peles.\"\n"); break;
            default: break;
        }
    }
    printf("=========================\n");
}

void imprimir_final_vitoria(TipoClasse classe) {
    printf("\n========================================\n");
    printf("           VITORIA SUPREMA!             \n");
    printf("========================================\n");
    switch(classe) {
        case CLASSE_GUERREIRO:
            printf("Alex limpa o sangue de sua lamina. O Lich caiu.\n");
            printf("Voce retorna como o Salvador de Eda e estende a mao para Eldraine.\n");
            printf("A honra do cla Draven foi restaurada, e um novo legado começa.\n");
            break;
        case CLASSE_NECROMANTE:
            printf("Nas cinzas do Lich, voce encontra a paz que buscava.\n");
            printf("Sua mae nao volta a vida, mas voce finalmente entende a morte.\n");
            printf("Voce deixa o Abismo, sabia e livre da sombra que a perseguia.\n");
            break;
        case CLASSE_SACERDOTE:
            printf("Thamus sente o calor de Aerion. Voce se tornou o Avatar da Chama Branca.\n");
            printf("O Abismo foi purificado e sua fe junto, Eda esta a salva por enquanto.\n");
            break;
        case CLASSE_HUNTERS:
            printf("O silencio reina. Ronan escuta os uivo alegre de Wolf, ambos vivos e com apenas um destino.\n");
            printf("Semanas depois... voce esta sentado na areia da praia, sentindo o nascer do sol sob sua pele. Sua casa finalmente recem construída atrás de você e com Wolf correndo atrás de alguns siris. A vida de caça acabou.\n");
            break;
        default: break;
    }
    printf("\nPARABENS! Voce completou INTO THE ABYSS.\n");
}

void imprimir_final_derrota(TipoClasse classe) {
    printf("\n========================================\n");
    printf("           FINAL TRAGICO...             \n");
    printf("========================================\n");
    switch(classe) {
        case CLASSE_GUERREIRO:
            printf("A corrupção do Abismo invade suas feridas, envenenando sua alma até que apenas obediência ao Lich permaneça.\n");
            printf("Eldraine chorará sua queda, incapaz de imaginar que você renasceu como o general sombrio que selará o destino de Eda.\n");
            break;
        case CLASSE_NECROMANTE:
            printf("A voz de Aldous ri: 'A eterna morte.' Voce servira ao Lich usando seus poderes para reviver os mortos pela eternidade.\n");
            break;
        case CLASSE_SACERDOTE:
            printf("Onde havia chamas, agora so resta o frio. O reino caira e voce não terá como impedir essa tragedia.\n");
            break;
        case CLASSE_HUNTERS:
            printf("Ronan cai ao lado de Wolf; o ultimo ganido do lobo parte seu coracao. Os pes que um dia sentiram a areia agora tocam apenas o frio do Abismo, e a brisa do mar se torna so um eco distante..\n");
            printf("Os sonhos de uma casa na praia, jamais construida, se desfazem nas sombras. A escuridao os engole por completo. O Abismo nao deixa sobreviventes.\n");
            break;
        default: break;
    }
    printf("\nGAME OVER.\n");
}

// --- INVENTÁRIO ---
void menu_inventario(Jogador* j) {
    if (lista_tamanho(j->inventario) == 0) {
        printf("\n>> Inventario vazio.\n");
        return;
    }

    printf("\n--- INVENTARIO ---\n");
    NoLista* atual = j->inventario->cabeca;
    int idx = 0;
    Item* itens_temp[50]; 

    while (atual != NULL) {
        Item* i = (Item*)atual->dados;
        itens_temp[idx] = i;
        
        printf("%d. %s ", idx+1, i->nome);
        
        // Exibe o status correto do item
        char bonus_str[20];
        switch(i->status_afetado) {
            case STATUS_DANO: strcpy(bonus_str, "Dano"); break;
            case STATUS_DEFESA: strcpy(bonus_str, "Def"); break;
            case STATUS_ATAQUE: strcpy(bonus_str, "Atk"); break;
            case STATUS_HP: strcpy(bonus_str, "HP Max"); break;
            default: strcpy(bonus_str, "Especial"); break;
        }

        if (i->tipo == ITEM_ARMA) printf("[Arma: +%d %s]", i->valor, bonus_str);
        else if (i->tipo == ITEM_ARMADURA) printf("[Armadura: +%d %s]", i->valor, bonus_str);
        else if (i->tipo == ITEM_ALIADO) printf("[Aliado: %s]", i->descricao);
        else if (i->tipo == ITEM_POCAO) printf("[Pocao: +%d %s]", i->valor, bonus_str);
        
        if (i == j->arma_equipada) printf(" <EQUIPADO>");
        if (i == j->armadura_equipada) printf(" <VESTIDO>");
        if (i == j->aliado_equipado) printf(" <ATIVO>");
        
        printf("\n");
        atual = atual->proximo;
        idx++;
    }
    
    printf("\nDigite o numero para Equipar/Usar (0 para sair): ");
    int esc = ler_input_seguro();
    
    if (esc > 0 && esc <= idx) {
        Item* alvo = itens_temp[esc-1];
        if (alvo->tipo == ITEM_POCAO) jogador_usar_pocao(j, alvo);
        else jogador_equipar_item(j, alvo);
    }
}

// --- COMBATE ---
int combate_executar(Jogador* j, Entidade* monstro) {
    printf("\n========================================\n");
    printf("!!! COMBATE: %s (Nv %d) !!!", monstro->nome, monstro->nivel);
    printf("\n========================================\n");
    printf("INIMIGO -> HP: %d | Def: %d | Dano: %d\n", 
           monstro->hp_max, monstro->defesa, monstro->dano_base);
    
    Fila* turno = fila_criar();
    fila_enqueue(turno, j->base); 
    for(int k=0; k < monstro->nivel; k++) fila_enqueue(turno, monstro);
    
    int fugiu = 0;
    int vitoria = 0;
    j->base->buff_dano = 0;

    while(!fila_vazia(turno)) {
        Entidade* atual = (Entidade*)fila_dequeue(turno);
        
        if (atual->hp_atual <= 0) continue; 
        if (j->base->hp_atual <= 0) break;
        if (monstro->hp_atual <= 0) { vitoria = 1; break; }

        // TURNO JOGADOR
        if (atual == j->base) {
            printf("\n[SEU TURNO] HP: %d/%d", j->base->hp_atual, jogador_calcular_hp_max_total(j));
            
            // Habilidade Aliado Sacerdote
            if (j->aliado_equipado && strstr(j->aliado_equipado->nome, "Sacerdote")) {
                int max_hp = jogador_calcular_hp_max_total(j);
                if (j->base->hp_atual < max_hp) {
                    j->base->hp_atual += 5;
                    printf(" (Sacerdote curou +5 HP)");
                }
            }
            printf("\n");

            // Habilidade Aliado Necromante
            if (j->aliado_equipado && strstr(j->aliado_equipado->nome, "Necromante")) {
                monstro->hp_atual -= 3;
                printf(">> Aliado Necromante drenou –3 HP do inimigo!\n");
                if (monstro->hp_atual <= 0) { vitoria = 1; break; }
            }

            int dano_total = jogador_calcular_dano_total(j);
            int atk_bonus = jogador_calcular_ataque_total(j);
            printf("Stats: Acerto +%d | Dano %d\n", atk_bonus, dano_total);
            printf("1. Atacar\n2. Inventario/Pocao\n3. Fugir\n> ");
            
            int acao = ler_input_seguro();
            
            if (acao == 1) {
                // Habilidade Caçador: Ataque Duplo
                int ataques = (j->base->classe == CLASSE_HUNTERS) ? 2 : 1;
                
                for (int i = 0; i < ataques; i++) {
                    if (monstro->hp_atual <= 0) break;
                    if (i > 0) printf("\n>> HABILIDADE CAÇADORES: Ataque Coordenado! \nVoce ataca novamente\n");

                    int dados = rolar_dados();
                    int final = dados + atk_bonus;
                    
                    printf(">> Ataque %d: Rolou %d + %d = %d (Def: %d)... \n", i+1, dados, atk_bonus, final, monstro->defesa);
                    
                    if (final >= monstro->defesa) {
                        monstro->hp_atual -= dano_total;
                        printf("ACERTOU! %d de dano.\n", dano_total);

                        // Habilidade Necromante: Toque Mortífero 
                        if (j->base->classe == CLASSE_NECROMANTE) {
                            j->base->hp_atual += dano_total / 3;
                            int toque_mortifero = dano_total / 3;
                            int max = jogador_calcular_hp_max_total(j);
                            if (j->base->hp_atual > max) j->base->hp_atual = max;
                            printf(">> HABILIDADE NECROMANTE: Toque Mortífero! \nVoce recupera %d de vida (+%d HP)\n", toque_mortifero, toque_mortifero);
                        }
                    } else {
                        printf("ERROU!\n");
                    }
                }
            } else if (acao == 2) {
                menu_inventario(j);
            } else if (acao == 3) {
                printf(">> Voce fugiu!\n");
                fugiu = 1; break; 
            }
        }
        // TURNO MONSTRO
        else {
            printf("\n[%s ATACA]\n", monstro->nome);
            int dados = rolar_dados();
            int final = dados + monstro->ataque;
            int def_jog = jogador_calcular_defesa_total(j);
            
            printf(">> Inimigo: Rolou %d + %d = %d (Sua Def: %d)... \n", dados, monstro->ataque, final, def_jog);
            
            if (final >= def_jog) {
                int dano_sofrido = monstro->dano_base;
                // Habilidade Guerreiro: Resistência 
                if (j->base->classe == CLASSE_GUERREIRO) {
                    dano_sofrido -= def_jog / 4;
                    int resistencia = def_jog / 4; 
                    if (dano_sofrido < 0) dano_sofrido = 0;
                    printf("HABILIDADE GUERREIRO: Resistência! \nVoce reduziu o dano recebido em –%d ", resistencia);
                }
                j->base->hp_atual -= dano_sofrido;
                printf("ATINGIDO! Sofreu %d de dano.\n", dano_sofrido);
            } else {
                printf("BLOQUEADO!\n");
            }
        }
        
        if (atual->hp_atual > 0) fila_enqueue(turno, atual);
    }
    
    j->base->buff_dano = 0;
    fila_destruir(turno);
    
    if (fugiu) return 0;
    if (vitoria) {
        printf("\n>> VOCE DERROTOU %s!\n", monstro->nome);
        // Habilidade Sacerdote: Benção de Aerion 
        if (j->base->classe == CLASSE_SACERDOTE) {
            j->base->hp_atual += j->base->hp_max / 3;
            int bencao_aerion = j->base->hp_max / 3;
            int max = jogador_calcular_hp_max_total(j);
            if (j->base->hp_atual > max) j->base->hp_atual = max;
            printf(">> HABILIDADE SACERDOTE: Benção de Aerion! \nVoce cura +%d HP.\n", bencao_aerion);
        }
        return 1;
    }
    return 0;
}

// --- MAIN ---
int main() {
    srand(time(NULL));
    char nome[50];
    
    printf("================================================\n");
    printf("             INTO THE ABYSS             \n");
    printf("================================================\n");
    printf("Digite seu nome: ");
    fgets(nome, 49, stdin);
    nome[strcspn(nome, "\n")] = 0; 

    printf("\nHá muito tempo, o Rei Aldous desceu ao Abismo \npara selar as Aberrações, criaturas que \nnascem da própria ferida do mundo. \nPara vencê-las, ele recorreu à magia proibida, \nsacrificando seu proprio corpo e alma.\n");
    printf("\nAgora Aldous desperta como um Lich, e seu \nrenascimento ameaça consumir todo reino Eda. \nPor ordem do Rei Delmondes, por juramentos \nou simplesmente suas próprias ambições.\n");
    printf("\nQuatro aventureiros escolheram descer até o abismo \npara impedir que o antigo salvador retorne como \no fim do reino que uma vez jurou proteger.\n");

    printf("\nEscolha sua Classe:\n");
    printf("1. O Guerreiro (Alex Draven)\n");
    printf("2. A Necromante (Lyssandra Valle)\n");
    printf("3. O Sacerdote (Thamus da Casa Solaris)\n");
    printf("4. Os Caçadores  (Ronan e Wolf)\n");
    printf("> ");
    
    int op_classe = ler_input_seguro();
    TipoClasse classe = CLASSE_GUERREIRO;
    if (op_classe == 2) classe = CLASSE_NECROMANTE;
    if (op_classe == 3) classe = CLASSE_SACERDOTE;
    if (op_classe == 4) classe = CLASSE_HUNTERS;

    Jogador* jogador = jogador_criar(nome, classe);
    
    printf("\nO Abismo esta sendo gerado... Embaralhando 53 cartas...\n");
    Pilha* dungeon = baralho_criar_dungeon(classe);
    pilha_embaralhar(dungeon); 

    int jogando = 1;
    
    while (jogando && jogador->base->hp_atual > 0) {
        // HUD ATUALIZADO
        int atk = jogador_calcular_ataque_total(jogador);
        int def = jogador_calcular_defesa_total(jogador);
        int dano = jogador_calcular_dano_total(jogador);
        int max_hp = jogador_calcular_hp_max_total(jogador);
        
        printf("\n--------------------------------------------------\n");
        printf("%s | Cartas: %d | Coringas: %d/2\n", jogador->nome_jogador, jogador->cartas_compradas, jogador->coringas_encontrados);
        printf("HP: %d/%d | Def: %d | Acerto: +%d | Dano: %d\n", jogador->base->hp_atual, max_hp, def, atk, dano);
        printf("--------------------------------------------------\n");
        
        printf("1. Explorar\n2. Inventario\n");
        if (jogador->coringas_encontrados >= 2) printf("3. !!! BOSS: LICH ALDOUS !!!\n");
        printf("0. Desistir\n> ");
        
        int opcao = ler_input_seguro();

        if (opcao == 0){
        printf("\nVoce corre atormentado pela escuridão, \napenas com aquela sensação de fracasso,  \no abismo é so para os fortes!!!");
        break;
        }
        else if (opcao == 2) menu_inventario(jogador);
        else if (opcao == 3 && jogador->coringas_encontrados >= 2) {
            Entidade* boss = entidade_criar("LICH REI ALDOUS", CLASSE_MONSTRO, 60, 8, 14, 8, 3);
            if (combate_executar(jogador, boss)) {
                imprimir_final_vitoria(classe);
                jogando = 0;
            } else {
                imprimir_final_derrota(classe);
                jogando = 0;
            }
            entidade_liberar(boss);
        }
        else if (opcao == 1) {
            if (pilha_tamanho(dungeon) == 0) {
                printf("\nO baralho acabou! Voce ficou preso... dentro do Abismo!\n");
                break;
            }

            Carta* carta = (Carta*)pilha_pop(dungeon);
            jogador->cartas_compradas++;
            printf("\n[CARTA %d] >> %s\n", jogador->cartas_compradas, carta->nome_carta);

            switch (carta->tipo_efeito) {
                case EFEITO_MONSTRO:
                    if (!combate_executar(jogador, carta->monstro_associado)) {
                        imprimir_final_derrota(classe);
                        jogando = 0;
                    }
                    break;
                case EFEITO_ITEM:
                    printf(">> Voce encontrou um item!\n");
                    Item* ni = item_criar(carta->item_associado->nome, carta->item_associado->tipo, carta->item_associado->status_afetado, carta->item_associado->valor, carta->item_associado->descricao);
                    jogador_adicionar_item(jogador, ni);
                    break;
                case EFEITO_EVENTO_CURA:
                    printf(">> Uma luz fraca e avermelhada surge no corredor. Um espírito benevolente toca seu ombro, curando suas feridas antes de desaparecer! \nVocê recupera +5 HP\n");
                    jogador->base->hp_atual += 5;
                    if(jogador->base->hp_atual > max_hp) jogador->base->hp_atual = max_hp;
                    break;
                case EFEITO_EVENTO_DANO:
                    printf(">> Você pisa em uma placa de pressão solta e ouve um 'clique'. Uma lâmina de veneno passa raspando por você! Você se esquiva, mas ainda sofre dano! \nVoce perde –3 HP\n");
                    jogador->base->hp_atual -= 3;
                    break;
                case EFEITO_EVENTO_LORE:
                    imprimir_lore(carta->id_evento, jogador->base->classe);
                    break;
                case EFEITO_EVENTO_GATO:
                    printf("Você ouve um miado fraco. Encolhido em um canto está um pequeno gato preto. Ele esfrega na sua perna, mia mais uma vez, e corre para a escuridão. Você se sente... estranhamente observado!\n");
                    break;
                case EFEITO_EVENTO_PIADA:
                    printf(">> Uma mulher surge da escuridão, ela aparenta vestir as mesmas roupas de outros ocultistas fanáticos e desaparece na escuridão.\n");
                    break;
                case EFEITO_EVENTO_PIADA_2:
                    printf(">> Uma figura misteriosa surge da escuridão, ela pronúncia palavras incompreensíveis e some ao seu piscar de olhos.\n");
                    break;
                case EFEITO_EVENTO_OURO:
                    printf(">> Você encontra o corpo de um aventureiro que não teve sorte. Ao lado dele, uma bolsa pesada de moedas. Pelo menos a jornada dele não foi em vão!\n");
                    break;
                case EFEITO_BOSS_KEY:
                    printf("\n!!! FILACTERIA DO LICH ENCONTRADO !!!\n");
                    printf("\nVOCE OBTEVE UMA DAS DUAS ESSÊNCIAS DO LICH\n");
                    jogador->coringas_encontrados++;
                    break;
                default: printf(">> Evento de ambiente estranho...\n"); break;
            }
            carta_liberar(carta);
        }
    }

    if (jogador->base->hp_atual <= 0 && jogando == 1) imprimir_final_derrota(classe);
    jogador_destruir(jogador);
    pilha_destruir(dungeon, carta_liberar);
    return 0;
}
