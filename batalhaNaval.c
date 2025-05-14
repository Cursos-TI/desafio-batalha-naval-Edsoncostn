#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

void startMap(int map[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            map[i][j] = AGUA;
        }
    }
}

void positionShip(int map[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int linha, coluna, direcao, valido;

    do {
        printf("Digite a linha inicial do navio (1 a 10): ");
        scanf("%d", &linha);
        printf("Digite a coluna inicial do navio (1 a 10): ");
        scanf("%d", &coluna);
        printf("Digite a direção do navio (0 = horizontal, 1 = vertical, 2 = diagonal ascendente, 3 = diagonal descendente): ");
        scanf("%d", &direcao);

        linha -= 1;
        coluna -= 1;
        valido = 1;

        for (int i = 0; i < 3; i++) {
            int x = linha + (direcao == 1 ? i : (direcao == 2 ? -i : (direcao == 3 ? i : 0)));
            int y = coluna + (direcao == 0 ? i : (direcao == 2 ? i : (direcao == 3 ? i : 0)));

            if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO || map[x][y] != AGUA) {
                valido = 0;
                break;
            }
        }

        if (!valido) {
            printf("\n O navio não pode ser posicionado aqui! Ele se sobrepõe ou sai do tabuleiro. Tente novamente.\n\n");
        }

    } while (!valido);

    for (int i = 0; i < 3; i++) {
        int x = linha + (direcao == 1 ? i : (direcao == 2 ? -i : (direcao == 3 ? i : 0)));
        int y = coluna + (direcao == 0 ? i : (direcao == 2 ? i : (direcao == 3 ? i : 0)));
        map[x][y] = NAVIO;
    }
}

// Cria a matriz correspondente ao ataque especial (Cone, Cruz ou Octaedro)
void createAbilityMatrix(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int tipo) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (tipo == 0) { // Cone apontado para baixo
                matriz[i][j] = (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i) ? 1 : 0;
            } else if (tipo == 1) { // Cruz
                matriz[i][j] = (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2) ? 1 : 0;
            } else { // Octaedro (losango)
                matriz[i][j] = (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2) ? 1 : 0;
            }
        }
    }
}

// Aplica um ataque aleatório ao tabuleiro
void applyRandomAbility(int map[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int origemX = rand() % TAMANHO_TABULEIRO;
    int origemY = rand() % TAMANHO_TABULEIRO;
    int tipoAtaque = rand() % 3; // Escolhe Cone (0), Cruz (1) ou Octaedro (2)

    createAbilityMatrix(habilidade, tipoAtaque);

    printf("\n🔴 Habilidade %s ativada em (%d, %d)!\n\n", tipoAtaque == 0 ? "Cone" : (tipoAtaque == 1 ? "Cruz" : "Octaedro"), origemX + 1, origemY + 1);

    int atingido = 0;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int x = origemX + i - TAMANHO_HABILIDADE / 2;
            int y = origemY + j - TAMANHO_HABILIDADE / 2;

            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO && habilidade[i][j] == 1) {
                if (map[x][y] == NAVIO) {
                    atingido = 1;
                } else {
                    map[x][y] = HABILIDADE;
                }
            }
        }
    }

    if (atingido) {
        printf("\n💥 Navio atingido! Ele foi destruído!\n");
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if (map[i][j] == NAVIO) {
                    map[i][j] = AGUA;
                }
            }
        }
    }
}

void showMap(int map[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    int map[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    startMap(map);

    printf("Posicione o primeiro navio:\n");
    positionShip(map);

    printf("Posicione o segundo navio:\n");
    positionShip(map);

    printf("\nMapa Inicial:\n");
    showMap(map);

    printf("\n⏳ Ativando habilidade 1...\n");
    applyRandomAbility(map);
    showMap(map);

    printf("\n⏳ Ativando habilidade 2...\n");
    applyRandomAbility(map);
    showMap(map);

    return 0;
}
