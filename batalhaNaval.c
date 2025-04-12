#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Nível Novato - Posicionamento dos Navios

void desenhaTabuleiro(int tabuleiro[10][10]) {
    char letra = 'A';

    printf("\n   \033[32m");

    for(int i=0; i<10; i++) {
        printf("%c ", letra);
        letra++;
    }

    for(int i=0; i<10; i++) {
        i < 9 ? printf("\n ") : printf("\n");
        printf("\033[32m%d \033[37m", i+1);

        for(int j=0; j<10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
    }

    printf("\n");
}

int main() {
    int navioX[2];
    int navioY[2];
    int inputNumero;
    char inputLetra;
    int tabuleiro[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };

    printf("\n --- Batalha Naval ---\n\n");
    desenhaTabuleiro(tabuleiro);

    // navioX
    do {
        printf("\nCoordenadas do navio horizontal:\nX [A-J]: ");
        scanf(" %c", &inputLetra);
    } while(inputLetra < 'A' || inputLetra > ('J' - 2));

    do {
        printf("Y [1-10]: ");
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 || inputNumero > 10);

    navioX[0] = inputNumero - 1;
    navioX[1] = (int) inputLetra - 65;

    for(int i=0; i<3; i++) {
        tabuleiro[navioX[0]][navioX[1] + i] = 3;
    }
    
    // navioY
    inicioNavioY:
    
    do {
        printf("\nCoordenadas do navio vertical:\nX [A-J]: ");
        scanf(" %c", &inputLetra);
    } while(inputLetra < 'A' || inputLetra > 'J');

    do {
        printf("Y [1-10]: ");
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 || inputNumero > (10 - 2));

    navioY[0] = inputNumero - 1;
    navioY[1] = (int) inputLetra - 65;

    for(int i=0; i<3; i++) {
        if(tabuleiro[navioY[0] + i][navioY[1]] != 0) {
            for(int j=i; j>0; j--) {
                tabuleiro[navioY[0] + (j - 1)][navioY[1]] = 0;
            }

            printf("Não pode haver colisão!\n");
            goto inicioNavioY;
        }

        tabuleiro[navioY[0] + i][navioY[1]] = 3;
    }

    desenhaTabuleiro(tabuleiro);

    printf("\n");
    return 0;
}
