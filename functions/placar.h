#ifndef PLACAR_H
#define PLACAR_H


typedef struct placar{
    int numero;
    char pecas_jogador;
    struct placar *proximo;
}placar;


#endif