#include <stdlib.h>
#include "hash.h"
#include "medicao.h"

// Estrutura do nó da lista encadeada
typedef struct NoHash {
    long long matricula;
    int pos; // Posição do aluno no vetor principal
    struct NoHash *prox;
} NoHash;

// Estrutura da Tabela Hash
struct TabelaHash {
    NoHash **tabela;
    int m; // Tamanho da tabela (número primo)
};

// Função de criação/alocação da tabela hash (essencial para o main.c)
TabelaHash *hash_cria(int m) {
    TabelaHash *h = (TabelaHash *)malloc(sizeof(TabelaHash));
    h->m = m;
    h->tabela = (NoHash **)calloc(m, sizeof(NoHash *)); // Inicializa todos os ponteiros com NULL
    return h;
}

// 1. Função hash (método da divisão)
int hash_funcao(long long chave, int m) {
    return (int)(chave % m);
}

// 2. Inserção no início da lista encadeada
void hash_insere(TabelaHash *h, long long matricula, int pos) {
    if (h == NULL) return;
    
    int idx = hash_funcao(matricula, h->m);
    
    NoHash *novo = (NoHash *)malloc(sizeof(NoHash));
    novo->matricula = matricula;
    novo->pos = pos;
    novo->prox = h->tabela[idx];
    
    h->tabela[idx] = novo;
}

// 3. Busca na tabela hash (some 1 a cada nó visitado)
int hash_busca(TabelaHash *h, long long matricula_busca) {
    if (h == NULL) return -1;
    
    int idx = hash_funcao(matricula_busca, h->m);
    NoHash *atual = h->tabela[idx];
    
    while (atual != NULL) {
        comparacoes++; // Conta cada nó visitado na lista (regra do trabalho)
        if (atual->matricula == matricula_busca) {
            return atual->pos;
        }
        atual = atual->prox;
    }
    
    return -1; // Não encontrado
}

// 4. Retorna o tamanho da maior lista de colisão
int hash_maior_lista(TabelaHash *h) {
    if (h == NULL) return 0;
    
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

// 5. Liberação de toda a memória alocada pela tabela hash
void hash_libera(TabelaHash *h) {
    if (h == NULL) return;
    
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
