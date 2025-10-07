// ============================================================================
//          PROJETO WAR ESTRUTURADO - NÍVEL AVENTUREIRO
// ============================================================================
// Objetivo:
// Adicionar a funcionalidade de ataque entre territórios, utilizando alocação
// dinâmica de memória e ponteiros para manipular dados.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
// FUNÇÃO DE ATAQUE
// ----------------------------------------------------------------------------
// A função atacar() simula uma batalha entre dois territórios.
// Usa rand() para gerar dados (1 a 6) para atacante e defensor.
// Se o atacante vencer, o defensor muda de cor e perde metade das tropas.
// Se perder, o atacante perde uma tropa.
// ============================================================================
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n🎲 Rolagem de dados:\n");
    printf(" Atacante (%s) tirou: %d\n", atacante->nome, dadoAtacante);
    printf(" Defensor (%s) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("➡️ O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = defensor->tropas / 2;
        printf(" O território %s agora pertence ao exército %s.\n",
               defensor->nome, defensor->cor);
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ----------------------------------------------------------------------------
// Responsável por:
// 1. Alocar dinamicamente o vetor de territórios.
// 2. Solicitar ao usuário os dados de cada território.
// 3. Permitir a simulação de um ataque.
// 4. Exibir os resultados atualizados.
// 5. Liberar a memória antes de encerrar o programa.
// ============================================================================
int main() {
    srand(time(NULL)); // Inicializa a semente para gerar números aleatórios

    int quantidade;
    Territorio* territorios;

    printf("=============================================\n");
    printf("   PROJETO WAR ESTRUTURADO - NÍVEL AVENTUREIRO\n");
    printf("=============================================\n\n");

    // Solicita ao usuário o número de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);

    // Alocação dinâmica de memória
    territorios = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro: memória insuficiente.\n");
        return 1;
    }

    printf("\nBem-vindo! Vamos cadastrar os territórios.\n");
    printf("Preencha as informações solicitadas abaixo.\n\n");

    // Cadastro dos territórios
    for (int i = 0; i < quantidade; i++) {
        printf("---- Território %d ----\n", i + 1);
        printf("Nome do território: ");
        scanf("%s", territorios[i].nome);
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");
    }

    // Exibição dos territórios cadastrados
    printf("\n=============================================\n");
    printf("      DADOS DOS TERRITÓRIOS CADASTRADOS\n");
    printf("=============================================\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor do exército: %s\n", territorios[i].cor);
        printf(" Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------------------\n");
    }

    // Simulação de ataque
    int atacanteIndex, defensorIndex;

    printf("\nEscolha o número do território atacante: ");
    scanf("%d", &atacanteIndex);
    printf("Escolha o número do território defensor: ");
    scanf("%d", &defensorIndex);

    // Validação simples de entrada
    if (atacanteIndex < 1 || atacanteIndex > quantidade ||
        defensorIndex < 1 || defensorIndex > quantidade) {
        printf("❌ Índice inválido!\n");
    } else if (strcmp(territorios[atacanteIndex - 1].cor,
                      territorios[defensorIndex - 1].cor) == 0) {
        printf("⚠️ Um território não pode atacar outro da mesma cor!\n");
    } else {
        atacar(&territorios[atacanteIndex - 1], &territorios[defensorIndex - 1]);
    }

    // Exibição dos dados após o ataque
    printf("\n=============================================\n");
    printf("     ESTADO DOS TERRITÓRIOS APÓS O ATAQUE\n");
    printf("=============================================\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor do exército: %s\n", territorios[i].cor);
        printf(" Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------------------\n");
    }

    // Liberação de memória
    free(territorios);
    printf("\nMemória liberada com sucesso. ✅\n");
    printf("Fim do nível aventureiro!\n");

    return 0;
}
