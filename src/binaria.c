#include "binaria.h"
#include "medicao.h"

int busca_binaria(Aluno *v, int n, long long matricula_busca) {
    int ini = 0;
    int fim = n - 1;
    
    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2;
        
        comparacoes++;
        
        if (v[meio].matricula == matricula_busca) {
            return meio; // Retorna a posição do aluno
        } else if (v[meio].matricula < matricula_busca) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1; 
}
