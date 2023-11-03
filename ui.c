#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "mapa.h"

char desenhoParede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoFantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoJogador[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhoVazioPonto[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhoVazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

char desenhoPilula[4][7] = {
    {" .-.  "},
    {" ' '  "},
    {" '_'  "},
    {"      "}
};

void imprimeParte(char desenho[4][7], int parte) {
    printf("%s", desenho[parte]);
}

void imprimeMapa(MAPA* m) {
    for (int i = 0; i < m->linhas; i++) {
        
        for (int parte = 0; parte < 4; parte++) {
            for (int j = 0; j < m->colunas; j++) {
                switch (m->matriz[i][j]) {
                    case FANTASMA:
                        imprimeParte(desenhoFantasma, parte);
                        break;

                    case JOGADOR:
                        imprimeParte(desenhoJogador, parte);
                        break;

                    case PILULA:
                        imprimeParte(desenhoPilula, parte);
                        break;

                    case VAZIO:
                        imprimeParte(desenhoVazio, parte);
                        break;

                    case VAZIO_PONTO:
                        imprimeParte(desenhoVazioPonto, parte);
                        break;

                    case PAREDE_HORIZONTAL:
                    case PAREDE_VERTICAL:
                        imprimeParte(desenhoParede, parte);
                        break;                    
                }
            }
            printf("\n");
        }
    }
}