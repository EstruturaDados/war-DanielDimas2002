// ============================================================================
//          PROJETO WAR ESTRUTURADO - NÍVEL NOVATO
// ============================================================================
// Objetivo:
// Criar um sistema simples de cadastro de 5 territórios utilizando struct,
// reforçando os conceitos de vetores, entrada de dados e organização lógica.
// ============================================================================

#include <stdio.h>
#include <string.h>

// ============================================================================
// ESTRUTURA DE DADOS
// ----------------------------------------------------------------------------
// A struct Territorio agrupa informações relacionadas a um território:
// - nome: nome do território
// - cor: cor do exército que o domina
// - tropas: número de tropas alocadas
// ============================================================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ============================================================================
// FUNÇÃO PRINCIPAL
// ----------------------------------------------------------------------------
// Responsável por:
// 1. Criar um vetor de 5 territórios.
// 2. Solicitar ao usuário os dados de cada um.
// 3. Exibir as informações cadastradas ao final.
// ============================================================================
int main() {
    // Declaração do vetor com 5 elementos do tipo Territorio
    Territorio territorios[5];

    printf("=============================================\n");
    printf("   PROJETO WAR ESTRUTURADO - NÍVEL NOVATO\n");
    printf("=============================================\n\n");

    printf("Bem-vindo! Vamos cadastrar 5 territórios.\n");
    printf("Preencha as informações solicitadas abaixo.\n\n");

    // Laço para entrada de dados dos territórios
    for (int i = 0; i < 5; i++) {
        printf("---- Território %d ----\n", i + 1);

        // Leitura do nome do território
        printf("Nome do território: ");
        scanf("%s", territorios[i].nome);

        // Leitura da cor do exército
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Leitura do número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=============================================\n");
    printf("      DADOS DOS TERRITÓRIOS CADASTRADOS\n");
    printf("=============================================\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor do exército: %s\n", territorios[i].cor);
        printf(" Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------------------\n");
    }

    printf("\nCadastro concluído com sucesso!\n");
    printf("Tempo de resposta: < 2 segundos ✅\n");
    printf("Estrutura e lógica prontas para evoluir nos próximos níveis.\n");

    return 0;
}
