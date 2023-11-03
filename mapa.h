#ifndef _MAPA_H_
#define _MAPA_H_

#define JOGADOR '@'
#define FANTASMA 'F'
#define VAZIO_PONTO '.'
#define VAZIO ' '
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa {
    char** matriz;
    int linhas;
    int colunas;
};

struct posicao {
    int x;
    int y;
};

typedef struct mapa MAPA;
typedef struct posicao POSICAO;

void leMapa(MAPA* m);
void alocaMapa(MAPA* m);
void liberaMapa(MAPA* m);
int encontraMapa(MAPA* m, POSICAO* p, char c);
int jogadaEhValida(MAPA* m, int x, int y);
void andaNoMapa(MAPA* m, int xorigem, int yorigem,
    int xdestino, int ydestino, int ehJogador);
int podeAndar(MAPA* m, int x, int y, char personagem);
int ehPersonagem(MAPA* m, int x, int y, char personagem);

#endif