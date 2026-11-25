#include <stdlib.h>
#include <stdio.h>
#include "arvoreb.h"
#include "medicao.h"

// Busca interna auxiliar para evitar chaves repetidas sem alterar 'comparacoes'
static int busca_interna(const NoB *x, int chave) {
    if (x == NULL) return -1;

    int i = 0;
    while (i < x->n && chave > x->chave[i]) {
        i++;
    }

    if (i < x->n && chave == x->chave[i]) {
        return x->pos[i];
    }

    if (x->folha) {
        return -1;
    }

    return busca_interna(x->filho[i], chave);
}

// 1. Busca principal na Árvore-B (soma 1 a cada nó visitado)
int arvb_busca(const ArvoreB *a, int chave) {
    if (a == NULL || a->raiz == NULL) return -1;

    const NoB *x = a->raiz;
    while (x != NULL) {
        comparacoes++; // Conta cada nó visitado

        int i = 0;
        while (i < x->n && chave > x->chave[i]) {
            i++;
        }

        if (i < x->n && chave == x->chave[i]) {
            return x->pos[i]; // Encontrou: devolve a posição no vetor
        }

        if (x->folha) {
            return -1; // Chegou na folha e não encontrou
        }

        x = x->filho[i];
    }

    return -1;
}

// 2. Função auxiliar para dividir o filho y do nó x na posição i
static void divide_filho(ArvoreB *a, NoB *x, int i) {
    int t = a->t;
    NoB *y = x->filho[i];

    // Cria um novo nó z que terá t-1 chaves usando a função pronta do projeto
    NoB *z = arvb_novo_no(a, y->folha);
    z->n = t - 1;

    // Copia as últimas t-1 chaves e posições de y para z
    for (int j = 0; j < t - 1; j++) {
        z->chave[j] = y->chave[j + t];
        z->pos[j] = y->pos[j + t];
    }

    // Se y não for folha, copia também os filhos correspondentes
    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            z->filho[j] = y->filho[j + t];
        }
    }

    // Ajusta o número de chaves em y
    y->n = t - 1;

    // Abre espaço nos filhos de x para receber z
    for (int j = x->n; j >= i + 1; j--) {
        x->filho[j + 1] = x->filho[j];
    }
    x->filho[i + 1] = z;

    // Abre espaço nas chaves de x para subir a chave mediana de y
    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
        x->pos[j + 1] = x->pos[j];
    }

    // Move a chave mediana de y para x
    x->chave[i] = y->chave[t - 1];
    x->pos[i] = y->pos[t - 1];

    // Incrementa o número de chaves em x
    x->n++;
}

// 3. Função auxiliar para inserir em um nó que não está cheio
static void insere_nao_cheio(ArvoreB *a, NoB *x, int chave, int pos) {
    int i = x->n - 1;

    if (x->folha) {
        // Encontra a posição correta e desloca as chaves maiores para a direita
        while (i >= 0 && chave < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            x->pos[i + 1] = x->pos[i];
            i--;
        }
        // Insere a nova chave
        x->chave[i + 1] = chave;
        x->pos[i + 1] = pos;
        x->n++;
    } else {
        // Encontra o filho que vai receber a nova chave
        while (i >= 0 && chave < x->chave[i]) {
            i--;
        }
        i++;

        // Verifica se o filho está cheio
        if (x->filho[i]->n == (2 * a->t - 1)) {
            divide_filho(a, x, i);
            if (chave > x->chave[i]) {
                i++;
            }
        }
        insere_nao_cheio(a, x->filho[i], chave, pos);
    }
}

// 4. Inserção principal na Árvore-B (evita chaves duplicadas)
void arvb_insere(ArvoreB *a, int chave, int pos) {
    if (a == NULL || a->t < 2) return;

    // Evita inserir matrículas repetidas
    if (busca_interna(a->raiz, chave) != -1) {
        return;
    }

    NoB *r = a->raiz;

    // Verifica se a árvore está vazia
    if (r == NULL) {
        a->raiz = arvb_novo_no(a, 1); // Cria raiz como folha
        a->raiz->chave[0] = chave;
        a->raiz->pos[0] = pos;
        a->raiz->n = 1;
        return;
    }

    // Verifica se a raiz está cheia (precisa de divisão)
    if (r->n == (2 * a->t - 1)) {
        NoB *s = arvb_novo_no(a, 0); // Nova raiz não é folha
        a->raiz = s;
        s->filho[0] = r;
        divide_filho(a, s, 0);
        insere_nao_cheio(a, s, chave, pos);
    } else {
        insere_nao_cheio(a, r, chave, pos);
    }
}

// Função auxiliar recursiva para calcular a altura da Árvore-B
static int altura_rec(const NoB *no) {
    if (no == NULL) return 0;
    if (no->folha) return 1;
    return 1 + altura_rec(no->filho[0]);
}

// 5. Retorna a altura da Árvore-B
int arvb_altura(const ArvoreB *a) {
    if (a == NULL) return 0;
    return altura_rec(a->raiz);
}

// Função auxiliar para o desafio de consulta por faixa
static int conta_faixa_rec(const NoB *x, int ini, int fim) {
    if (x == NULL) return 0;

    int count = 0;
    int i = 0;

    while (i < x->n && x->chave[i] < ini) {
        i++;
    }

    if (!x->folha) {
        count += conta_faixa_rec(x->filho[i], ini, fim);
    }

    while (i < x->n && x->chave[i] <= fim) {
        if (x->chave[i] >= ini) {
            count++;
        }
        i++;
        if (!x->folha) {
            count += conta_faixa_rec(x->filho[i], ini, fim);
        }
    }

    return count;
}

// 6. Desafio (bônus): consulta por faixa
int arvb_conta_faixa(const ArvoreB *a, int ini, int fim) {
    if (a == NULL || a->raiz == NULL || ini > fim) return 0;
    return conta_faixa_rec(a->raiz, ini, fim);
}
