#ifndef _PACMAN_H_
#define _PACMAN_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

void move(char direcao);
int acabou();
void fantasmas();
void defineDestinoFantasma(int xatual, int yatual, 
    int* xdestino, int* ydestino);
void explodePilula2(int x, int y, int somax, int somay, int qtd);
void explodePilula(int qtd);

#endif