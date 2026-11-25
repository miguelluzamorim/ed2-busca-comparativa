#include "binaria.h"
#include "medicao.h"

int busca_binaria(Aluno *v, int n, long long matricula_busca) {
    int ini = 0;
    int fim = n - 1;
    
    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2;
        
        comparacoes++; // Conta a examinação do elemento do meio
        
        if (v[meio].matricula == matricula_busca) {
            return meio; // Retorna a posição do aluno
        } else if (v[meio].matricula < matricula_busca) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1; // Não encontrado
}
int arvb_conta_faixa(const ArvoreB *a, int ini, int fim) {
    (void)a; (void)ini; (void)fim;
    return -1;
}
