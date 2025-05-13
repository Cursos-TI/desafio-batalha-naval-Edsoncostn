#include <stdio.h>


void startMap (int map[10][10]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            map[i][j] = 0; // inicializa o mapa com 0 = água
        }
    }
}

void positionShip(int map[10][10]) {
    int linha, coluna, direcao, valido;

    do {
        printf("Digite a linha inicial do navio (1 a 10)\n");
        scanf("%d", &linha);

        printf("Digite a coluna inicial do navio (1 a 10)\n");
        scanf("%d", &coluna);

        printf("Digite a direção do navio (0 = horizontal, 1 = vertical)\n");
        scanf("%d", &direcao);

        linha -= 1; // ajusta a linha para o índice do array
        coluna -= 1; // ajusta a coluna para o índice do array

        // Verifica se há espaço disponível para posicionar o navio
        valido = 1; // Assume que a posição é válida
        
        for (int i = 0; i < 3; i++) {
            if (direcao == 0) { // Horizontal
                if (coluna + i >= 10 || map[linha][coluna + i] != 0) {
                    valido = 0;
                    break;
                }
            } else if (direcao == 1) { // Vertical
                if (linha + i >= 10 || map[linha + i][coluna] != 0) {
                    valido = 0;
                    break;
                }
            } else {
                printf("Direção inválida!\n");
                valido = 0;
                break;
            }
        }

        if (!valido) {
            printf("\n O navio não pode ser posicionado aqui! Ele se sobrepõe ou sai do tabuleiro. Tente novamente.\n\n");
        }

    } while (!valido); // Repete até encontrar uma posição válida

    // Se a posição for válida, o navio é marcado no mapa
    for (int i = 0; i < 3; i++) {
        if (direcao == 0) {
            map[linha][coluna + i] = 3;
        } else {
            map[linha + i][coluna] = 3;
        }
    }
}

void showMap(int map[10][10]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", map[i][j]); // imprime o mapa na tela
        }
        printf("\n"); // pula para a próxima linha
    }
}
    





int main(){



    int index;
    int map[10][10]; // cria o mapa 10x10

    startMap(map); // inicializa o mapa

    printf("Posicione o primeiro navio:\n");
    positionShip(map); // chama a função para posicionar o navio no mapa

    printf("Posicione o segundo navio:\n");
    positionShip(map); // chama a função para posicionar o navio no mapa

   
    showMap(map); // chama a função para mostrar o mapa na tela


    

return 0;
}
