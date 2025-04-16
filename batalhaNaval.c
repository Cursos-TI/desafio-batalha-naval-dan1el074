#include <stdio.h>

#define TAMANHO 10

void desenhaTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    char letra = 'A';

    printf("\n   \033[37m");

    for(int i=0; i<TAMANHO; i++) {
        printf("%c ", letra);
        letra++;
    }

    for(int i=0; i<TAMANHO; i++) {
        i < 9 ? printf("\n ") : printf("\n");
        printf("\033[37m%d \033[34m", i+1);

        /*
            0 - mar
            1 - habilidade
            3 - navio
            9 - hit
        */
        for(int j=0; j<TAMANHO; j++) {            
            switch(tabuleiro[i][j]) {
                case 0:
                    printf("\033[34m%d ", tabuleiro[i][j]);
                    break;
                case 1:
                    printf("\033[33m%d ", tabuleiro[i][j]);
                    break;
                case 3:
                    printf("\033[37m%d ", tabuleiro[i][j]);
                    break;
                case 9:
                    printf("\033[31m%d ", 3);
                    break;
            }
        }
    }

    printf("\n \033[37m");
}

void habilidadeCone(int tabuleiro[TAMANHO][TAMANHO], int coordenadaHabilidade[2], int areaHabilidade[2]) {
    for(int i=0; i<areaHabilidade[0]; i++) {
        int inicio = 2 - i;
        int final = 2 + i;

        for(int j=0; j<areaHabilidade[1]; j++) {
            if(j>=inicio && j<=final) {
                if(tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + j] == 0) {
                    tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + j] = 1;
                } else {
                    tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + j] = 9;
                }
            }
        }
    }

    printf("\n --- Habilidade Cone ---\n");
    desenhaTabuleiro(tabuleiro);
}

void habilidadeCruz(int tabuleiro[TAMANHO][TAMANHO], int coordenadaHabilidade[2], int areaHabilidade[2]) {
    int meio = 2;
    int preencher = 0;

    for(int i=0; i<areaHabilidade[0]; i++) {
        for(int j=0; j<areaHabilidade[1]; j++) {
            if(preencher == 1 || j == meio) {
                if(tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + j] == 0) {
                    tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + j] = 1;
                } else {
                    tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + j] = 9;
                }
            }
        }
        preencher > 0 ? preencher-- : preencher++;
    }

    printf("\n --- Habilidade Cruz ---\n");
    desenhaTabuleiro(tabuleiro);
}

void habilidadeOctaedro(int tabuleiro[TAMANHO][TAMANHO], int coordenadaHabilidade[2], int areaHabilidade[2]) {
    for(int i=0, j=0; i<areaHabilidade[0]; i++, j % 2 == 0 ? j++ : j--) {
        int inicio = 2 - j;
        int final = 2 + j;

        for(int k=0; k<areaHabilidade[1]; k++) {
            if(k>=inicio && k<=final) {
                if(tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + k] == 0) {
                    tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + k] = 1;
                } else {
                    tabuleiro[(coordenadaHabilidade[0] - 1) + i][(coordenadaHabilidade[1] - 2) + k] = 9;
                }
            }
        }
    }

    printf("\n --- Habilidade Octaedro ---\n");
    desenhaTabuleiro(tabuleiro);
}

void inputHabilidade(int tabuleiro[TAMANHO][TAMANHO], int tipoHabilidade) {
    int tabuleiroHabilidade[TAMANHO][TAMANHO];
    int coordenadaHabilidade[2];
    int areaHabilidade[2] = {3, 5};
    int inputNumero;
    char inputLetra;

    // copia tabuleiro base
    for(int i=0; i<TAMANHO; i++) {
        for(int j=0; j<TAMANHO; j++) {
            tabuleiroHabilidade[i][j] = tabuleiro[i][j];
        }
    }

    // pega coordenadas
    do {
        printf("\nCoordenadas da habilidade %s:\nX [A-%c]: ", tipoHabilidade == 1 ? "cone" : (tipoHabilidade == 2 ? "cruz" : "octaedro"), 'A' + (TAMANHO - 1));
        scanf(" %c", &inputLetra);
    } while(inputLetra < 'A' + (areaHabilidade[1] / 2) || inputLetra > 'A' + TAMANHO - (areaHabilidade[1] / 2) - 1);

    do {
        printf("Y [1-%d]: ", TAMANHO);
        scanf(" %d", &inputNumero);
    } while(inputNumero < 1 + (areaHabilidade[0] / 2) || inputNumero > TAMANHO - (areaHabilidade[0] / 2));

    coordenadaHabilidade[0] = inputNumero - 1;
    coordenadaHabilidade[1] = (int) inputLetra - 65;

    // executa habilidades
    switch(tipoHabilidade) {
        case 1:
            habilidadeCone(tabuleiroHabilidade, coordenadaHabilidade, areaHabilidade);
            break;
        case 2:
            habilidadeCruz(tabuleiroHabilidade, coordenadaHabilidade, areaHabilidade);
            break;
        case 3:
            habilidadeOctaedro(tabuleiroHabilidade, coordenadaHabilidade, areaHabilidade);
            break;
    }

    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int navioHorizontal[2], navioVertical[2], navioDiagonal1[2], navioDiagonal2[2];
    int inputNumero;
    char inputLetra;

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
        printf("\nCoordenadas do navio diagonal (\\):\nX [A-%c]: ", 'A' + (TAMANHO - 1));
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
        printf("\nCoordenadas do navio diagonal (/):\nX [A-%c]: ", 'A' + (TAMANHO - 1));
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

    /*
        1 - habilidade cone
        2 - habilidade cruz
        3 - habilidade octaedro
    */
    inputHabilidade(tabuleiro, 1);
    inputHabilidade(tabuleiro, 2);
    inputHabilidade(tabuleiro, 3);
}
