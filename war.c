// ============================================================================
//          PROJETO WAR ESTRUTURADO - NÍVEL MESTRE
// ============================================================================
// Objetivo:
// Implementar a funcionalidade de missões estratégicas, adicionando uma camada
// de estratégia ao sistema e consolidando o uso de modularização, ponteiros e
// alocação dinâmica de memória.
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// ESTRUTURA DE DADOS
// ----------------------------------------------------------------------------
// Representa um território do jogo, com nome, cor do exército e tropas.
// ============================================================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ============================================================================
// FUNÇÃO: atacar()
// ----------------------------------------------------------------------------
// Simula uma batalha entre dois territórios. Cada lado lança um dado (1 a 6).
// O vencedor altera as tropas e/ou o domínio do território.
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
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        if (atacante->tropas > 0) {
            atacante->tropas--;
        }
    }
}

// ============================================================================
// FUNÇÃO: atribuirMissao()
// ----------------------------------------------------------------------------
// Sorteia uma missão aleatória entre as disponíveis e a copia para a missão
// do jogador, alocada dinamicamente.
// ============================================================================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// ============================================================================
// FUNÇÃO: verificarMissao()
// ----------------------------------------------------------------------------
// Verifica se a missão do jogador foi cumprida. Implementação simples que
// retorna 1 se houver pelo menos 3 territórios com a cor do jogador.
// ============================================================================
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    int contador = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            contador++;
        }
    }

    // Condição genérica de vitória: 3 territórios dominados
    if (contador >= 3) {
        return 1;
    }
    return 0;
}

// ============================================================================
// FUNÇÃO: exibirMapa()
// ----------------------------------------------------------------------------
// Exibe todos os territórios cadastrados com suas informações atualizadas.
// ============================================================================
void exibirMapa(Territorio* territorios, int quantidade) {
    printf("\n=============================================\n");
    printf("            ESTADO ATUAL DO MAPA\n");
    printf("=============================================\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor do exército: %s\n", territorios[i].cor);
        printf(" Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------------------------\n");
    }
}

// ============================================================================
// FUNÇÃO: liberarMemoria()
// ----------------------------------------------------------------------------
// Libera a memória alocada dinamicamente tanto para os territórios quanto
// para as missões dos jogadores.
// ============================================================================
void liberarMemoria(Territorio* mapa, char* missaoJogador1, char* missaoJogador2) {
    free(mapa);
    free(missaoJogador1);
    free(missaoJogador2);
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ----------------------------------------------------------------------------
// 1. Aloca memória para os territórios.
// 2. Cadastra territórios e atribui missões a dois jogadores.
// 3. Permite um ataque e verifica se há vencedor.
// 4. Exibe o estado final e libera toda a memória.
// ============================================================================
int main() {
    srand(time(NULL));

    int quantidade;
    printf("=============================================\n");
    printf("   PROJETO WAR ESTRUTURADO - NÍVEL MESTRE\n");
    printf("=============================================\n\n");

    // Cadastro de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);

    Territorio* territorios = (Territorio*)calloc(quantidade, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro: memória insuficiente.\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\n---- Território %d ----\n", i + 1);
        printf("Nome do território: ");
        scanf("%s", territorios[i].nome);
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Criação das missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas vermelhas",
        "Controlar metade do mapa",
        "Manter 5 territórios com tropas acima de 10",
        "Dominar todos os territórios azuis"
    };
    int totalMissoes = 5;

    // Alocação dinâmica para as missões dos jogadores
    char* missaoJogador1 = (char*)malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*)malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\nMissão do Jogador 1: %s\n", missaoJogador1);
    printf("Missão do Jogador 2: %s\n", missaoJogador2);

    // Exibe o mapa inicial
    exibirMapa(territorios, quantidade);

    // Escolha de ataque
    int atacanteIndex, defensorIndex;
    printf("\nEscolha o número do território atacante: ");
    scanf("%d", &atacanteIndex);
    printf("Escolha o número do território defensor: ");
    scanf("%d", &defensorIndex);

    if (atacanteIndex < 1 || atacanteIndex > quantidade ||
        defensorIndex < 1 || defensorIndex > quantidade) {
        printf("❌ Índice inválido!\n");
    } else if (strcmp(territorios[atacanteIndex - 1].cor,
                      territorios[defensorIndex - 1].cor) == 0) {
        printf("⚠️ Um território não pode atacar outro da mesma cor!\n");
    } else {
        atacar(&territorios[atacanteIndex - 1], &territorios[defensorIndex - 1]);
    }

    // Exibe o mapa atualizado
    exibirMapa(territorios, quantidade);

    // Verifica se algum jogador cumpriu sua missão
    int jogador1Venceu = verificarMissao(missaoJogador1, territorios, quantidade, "azul");
    int jogador2Venceu = verificarMissao(missaoJogador2, territorios, quantidade, "vermelho");

    if (jogador1Venceu) {
        printf("\n🏆 O Jogador 1 cumpriu sua missão: %s\n", missaoJogador1);
    } else if (jogador2Venceu) {
        printf("\n🏆 O Jogador 2 cumpriu sua missão: %s\n", missaoJogador2);
    } else {
        printf("\nNenhum jogador cumpriu sua missão ainda.\n");
    }

    liberarMemoria(territorios, missaoJogador1, missaoJogador2);

    printf("\nMemória liberada com sucesso. ✅\n");
    printf("Fim do Nível Mestre!\n");

    return 0;
}
