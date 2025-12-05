#ifndef FILA_H
#define FILA_H

typedef struct NoFila {
    void* dados;
    struct NoFila* proximo;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
} Fila;

// --- Funções ---
Fila* fila_criar();
void fila_destruir(Fila* f); // Não libera os dados internos, só a estrutura
void fila_enqueue(Fila* f, void* dados); // Entra na fila
void* fila_dequeue(Fila* f);             // Sai da fila
int fila_vazia(Fila* f);

#endif
