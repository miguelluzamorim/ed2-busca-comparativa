#include "ordenacao.h"
#include "medicao.h"

// 1. Insertion Sort (Ordenação por Inserção)
void ordena_insercao(Aluno *v, int n) {
    for (int i = 1; i < n; i++) {
        Aluno x = v[i]; // Guarda o Aluno inteiro
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++; // Conta a comparação entre a matrícula e o elemento atual
            if (v[j].matricula > x.matricula) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = x;
    }
}

// Função auxiliar recursiva para o Quicksort
static void quick_rec(Aluno *v, int ini, int fim) {
    if (ini >= fim) return;

    // Usa como pivô a matrícula do elemento do meio
    int meio = ini + (fim - ini) / 2;
    long long pivo_mat = v[meio].matricula;

    int i = ini;
    int j = fim;

    while (i <= j) {
        // Compara a matrícula do elemento da esquerda com o pivô
        while (1) {
            comparacoes++;
            if (v[i].matricula < pivo_mat) {
                i++;
            } else {
                break;
            }
        }

        // Compara a matrícula do elemento da direita com o pivô
        while (1) {
            comparacoes++;
            if (v[j].matricula > pivo_mat) {
                j--;
            } else {
                break;
            }
        }

        // Se os ponteiros não se cruzaram, troca os structs inteiros de lugar
        if (i <= j) {
            Aluno temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            j--;
        }
    }

    // Chamadas recursivas para as subpartições
    if (ini < j) quick_rec(v, ini, j);
    if (i < fim) quick_rec(v, i, fim);
}

// 2. Quicksort
void ordena_quick(Aluno *v, int n) {
    if (n > 1) {
        quick_rec(v, 0, n - 1);
    }
}
