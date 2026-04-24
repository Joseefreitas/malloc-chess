#ifndef MEU_JOGO_H
#define MEU_JOGO_H

void setpecas(pecas *jogador, int quant_pecas,int time);

pecas *allocar_memoria(int quantidade);

void movimento_cavalo(pecas *jogador , int unity_control);

void movimentopecas(pecas *jogador, int unity_control);

#endif