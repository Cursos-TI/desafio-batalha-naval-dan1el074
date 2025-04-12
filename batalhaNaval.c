#include <stdio.h>

#define TAMANHO 10

// Desafio Batalha Naval - MateCheck
// Nível Aventureiro - Posicionamento dos Navios

void desenhaTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    char letra = 'A';

    printf("\n   \033[32m");

    for(int i=0; i<TAMANHO; i++) {
        printf("%c ", letra);
        letra++;
    }

    for(int i=0; i<TAMANHO; i++) {
        i < 9 ? printf("\n ") : printf("\n");
        printf("\033[32m%d \033[37m", i+1);

        for(int j=0; j<TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
    }

    printf("\n");
}

int main() {
    int navioHorizontal[2];
    int navioVertical[2];
    int navioDiagonal1[2];
    int navioDiagonal2[2];

    int inputNumero;
    char inputLetra;
    int tabuleiro[TAMANHO][TAMANHO];

    // inicializa tabuleiro
    for(int i=0; i<TAMANHO; i++) {
        for(int j=0; j<TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    printf("\n --- Batalha Naval %dx%d ---\n", TAMANHO, TAMANHO);
    desenhaTabuleiro(tabuleiro);

    // navioHorizontal
    do {
        printf("\nCoordenadas do navio horizontal:\nX [A-%c]: ", 'A' + (TAMANHO - 1));
        scanf(" %c", &inputLetra);
    } while(inputLetra < 'A' || inputLetra > (('A' + (TAMANHO - 1)) - 2));

    do {
        printf("Y [1-%d]: ", TAMANHO);
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 || inputNumero > TAMANHO);

    navioHorizontal[0] = inputNumero - 1;
    navioHorizontal[1] = (int) inputLetra - 65;

    for(int i=0; i<3; i++) {
        tabuleiro[navioHorizontal[0]][navioHorizontal[1] + i] = 3;
    }
    
    // navioVertical
    inicioNavioVertical:
    
    do {
        printf("\nCoordenadas do navio vertical:\nX [A-%c]: ", 'A' + (TAMANHO - 1));
        scanf(" %c", &inputLetra);
    } while(inputLetra < 'A' || inputLetra > ('A' + (TAMANHO - 1)));

    do {
        printf("Y [1-%d]: ", TAMANHO);
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 || inputNumero > (TAMANHO - 2));

    navioVertical[0] = inputNumero - 1;
    navioVertical[1] = (int) inputLetra - 65;

    for(int i=0; i<3; i++) {
        // trata colisão
        if(tabuleiro[navioVertical[0] + i][navioVertical[1]] != 0) {
            while(i>0) {
                tabuleiro[navioVertical[0] + (i - 1)][navioVertical[1]] = 0;
                i--;
            }

            printf("Não pode haver colisão!\n");
            goto inicioNavioVertical;
        }

        tabuleiro[navioVertical[0] + i][navioVertical[1]] = 3;
    }
    
    // navioDiagonal1
    inicioNavioDiagonal1:
    
    do {
        printf("\nCoordenadas do primeiro navio diagonal:\nX [A-%c]: ", 'A' + (TAMANHO - 1));
        scanf(" %c", &inputLetra);
    } while(inputLetra < 'A' || inputLetra > (('A' + (TAMANHO - 1)) - 2));

    do {
        printf("Y [1-%d]: ", TAMANHO);
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 || inputNumero > (TAMANHO - 2));

    navioDiagonal1[0] = inputNumero - 1;
    navioDiagonal1[1] = (int) inputLetra - 65;

    for(int i=0; i<3; i++) {
        // trata colisão
        if(tabuleiro[navioDiagonal1[0] + i][navioDiagonal1[1] + i] != 0) {
            while(i>0) {
                tabuleiro[navioDiagonal1[0] + (i - 1)][navioDiagonal1[1] + (i - 1)] = 0;
                i--;
            }

            printf("Não pode haver colisão!\n");
            goto inicioNavioDiagonal1;
        }

        tabuleiro[navioDiagonal1[0] + i][navioDiagonal1[1] + i] = 3;
    }
    
    // navioDiagonal2
    inicioNavioDiagonal2:
    
    do {
        printf("\nCoordenadas do segundo navio diagonal:\nX [A-%c]: ", 'A' + (TAMANHO - 1));
        scanf(" %c", &inputLetra);
    } while(inputLetra < ('A') + 2 || inputLetra > 'A' + (TAMANHO - 1));

    do {
        printf("Y [1-%d]: ", TAMANHO);
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 || inputNumero > TAMANHO - 2);

    navioDiagonal2[0] = inputNumero - 1;
    navioDiagonal2[1] = (int) inputLetra - 65;

    for(int i=0; i<3; i++) {
        // trata colisão
        if(tabuleiro[navioDiagonal2[0] + i][navioDiagonal2[1] - i] != 0) {
            while(i>0) {
                tabuleiro[navioDiagonal2[0] + (i - 1)][navioDiagonal2[1] - (i - 1)] = 0;
                i--;
            }

            printf("Não pode haver colisão!\n");
            goto inicioNavioDiagonal2;
        }

        tabuleiro[navioDiagonal2[0] + i][navioDiagonal2[1] - i] = 3;
    }

    desenhaTabuleiro(tabuleiro);

    printf("\n");
    return 0;
}
