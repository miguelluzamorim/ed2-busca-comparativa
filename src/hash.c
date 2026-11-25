#include <stdlib.h>
#include "hash.h"
#include "medicao.h"

// Estrutura do nó da lista encadeada (exemplo comum)
typedef struct NoHash {
    long long matricula;
    int pos; // posição do aluno no vetor principal
    struct NoHash *prox;
} NoHash;

struct TabelaHash {
    NoHash **tabela;
    int m; // tamanho da tabela (número primo)
};

int hash_funcao(long long chave, int m) {
    return (int)(chave % m);
}

void hash_insere(TabelaHash *h, long long matricula, int pos) {
    int idx = hash_funcao(matricula, h->m);
    
    NoHash *novo = (NoHash *)malloc(sizeof(NoHash));
    novo->matricula = matricula;
    novo->pos = pos;
    novo->prox = h->tabela[idx];
    
    h->tabela[idx] = novo;
}

int hash_busca(TabelaHash *h, long long matricula_busca) {
    int idx = hash_funcao(matricula_busca, h->m);
    NoHash *atual = h->tabela[idx];
    
    while (atual != NULL) {
        comparacoes++; // Conta cada nó visitado na lista
        if (atual->matricula == matricula_busca) {
            return atual->pos;
        }
        atual = atual->prox;
    }
    
    return -1;
}

int hash_maior_lista(TabelaHash *h) {
    int maior = 0;
    for (int i = 0; i < h->m; i++) {
        int tam = 0;
        NoHash *atual = h->tabela[i];
        while (atual != NULL) {
            tam++;
            atual = atual->prox;
        }
        if (tam > maior) {
            maior = tam;
        }
    }
    return maior;
}

void hash_libera(TabelaHash *h) {
    if (!h) return;
    for (int i = 0; i < h->m; i++) {
        NoHash *atual = h->tabela[i];
        while (atual != NULL) {
            NoHash *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(h->tabela);
    free(h);
}
