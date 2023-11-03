#include <stdio.h>
#include <stdlib.h>
#include "mapa.h" 

void andaNoMapa(MAPA* m, int xorigem, int yorigem,
    int xdestino, int ydestino, int ehJogador){
    
    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xorigem][yorigem] = VAZIO_PONTO;
    
    if(ehJogador){
        m->matriz[xorigem][yorigem] = VAZIO;
    }
    
    m->matriz[xdestino][ydestino] = personagem;
}

int jogadaEhValida(MAPA* m, int x, int y) {
    return  ((x < m->linhas && y > 0) && (y < m->colunas && y > 0)) &&
            (m->matriz[x][y] != PAREDE_VERTICAL && m->matriz[x][y] != PAREDE_HORIZONTAL);
}

int ehPersonagem(MAPA* m, int x, int y, char personagem) {
    return m->matriz[x][y] == personagem;
}

int podeAndar(MAPA* m, int x, int y, char personagem) {
    return jogadaEhValida(m, x, y) && !ehPersonagem(m, x, y, personagem);
}

int encontraMapa(MAPA* m, POSICAO* p, char c) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            if (m->matriz[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }     
    }

    return 0;
}

void leMapa(MAPA* m) {
    FILE *f;
    f = fopen("mapa.txt", "r");
    if (f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));

    alocaMapa(m);
    
    for (int i = 0; i < m->linhas; i++) {
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}

void alocaMapa(MAPA* m) {
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for (int i = 0; i < m->linhas; i++) {
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1)); 
    }
}

void liberaMapa(MAPA* m) {
    for (int i = 0; i < m->linhas; i++) {
        free(m->matriz[i]);
    }
    free(m->matriz);
}
