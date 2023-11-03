#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "mapa.h" 
#include "ui.h"

MAPA m;
POSICAO jogador;
int pilulas = 0;

void defineDestinoFantasma(int xatual, int yatual, 
    int* xdestino, int* ydestino) {
    
    int opcoes[4][2] = {
        {xatual, yatual - 1},
        {xatual + 1, yatual},
        {xatual, yatual + 1},
        {xatual - 1, yatual}
    };

    srand(time(0));
    for (int i = 0; i < 10; i++){
        int posicao = rand() % 4;

        if (podeAndar(&m, opcoes[posicao][0], opcoes[posicao][1], FANTASMA)){
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
        }
    }
}

void fantasmas() {
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            if (m.matriz[i][j] == FANTASMA) {
                int icopia = i;
                int jcopia = j;
                defineDestinoFantasma(i, j, &icopia, &jcopia);
                andaNoMapa(&m, i, j, icopia, jcopia, 0);
                
                if ( i > icopia){
                    i--;
                }else if (i < icopia) {
                    i++;
                }else if (j > jcopia) {
                    j--;
                }else if (j < jcopia) {
                    j++;
                }
            }
        }
    }
}

int acabou() {
    POSICAO pos;
    int temPacmanNoMapa = encontraMapa(&m, &pos, JOGADOR);
    int temPontoNoMapa = encontraMapa(&m, &pos, VAZIO_PONTO);
    if (!temPacmanNoMapa) {
        system("clear");
        printf("Pilulas: %d\n", pilulas);
        imprimeMapa(&m);
        printf("Você Perdeu! Um fantasma te matou!\n");
    }

    if (!temPontoNoMapa) {
        system("clear");
        printf("Pilulas: %d\n", pilulas);
        imprimeMapa(&m);
        printf("Você Venceu! Não resta mais nenhum ponto no mapa!\n");
    }

    return !temPacmanNoMapa || !temPontoNoMapa;
}

void move(char direcao) {
    int x = jogador.x;
    int y = jogador.y;

    switch (direcao) {
        case ESQUERDA:
            jogador.y--;
            break;
        case CIMA:
            jogador.x--;
            break;
        case BAIXO:
            jogador.x++;
            break;
        case DIREITA:
            jogador.y++;
            break;
        default:
            return;                
    }

    if (!jogadaEhValida(&m, jogador.x, jogador.y)) {
        jogador.x = x;
        jogador.y = y;
        return;
    }

    if (ehPersonagem(&m, jogador.x, jogador.y, PILULA)) {
        pilulas++;
    }

    andaNoMapa(&m, x, y, jogador.x, jogador.y, 1);
}

void explodePilula(int qtd) {
    if (pilulas > 0){
        explodePilula2(jogador.x, jogador.y, 0, 1, qtd);
        explodePilula2(jogador.x, jogador.y, 0, -1, qtd);
        explodePilula2(jogador.x, jogador.y, 1, 0, qtd);
        explodePilula2(jogador.x, jogador.y, -1, 0, qtd);

        pilulas--;
    }
}

void explodePilula2(int x, int y, int somax, int somay, int qtd) {
    int novox = x + somax;
    int novoy = y + somay;
    
    if ((qtd == 0) || (!jogadaEhValida(&m, novox, novoy))) return;

    m.matriz[novox][novoy] = VAZIO_PONTO;
    explodePilula2(novox, novoy, somax, somay, qtd - 1);
}

void main() {
    
    leMapa(&m);
    encontraMapa(&m, &jogador, JOGADOR);

    do {
        system("clear");
        printf("Pilulas: %d\n", pilulas);
        imprimeMapa(&m);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodePilula(3);
        fantasmas();

    } while (!acabou());

    liberaMapa(&m);
}