#ifndef MEU_JOGO_H
#define MEU_JOGO_H


int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras);

void ataque_pecas(pecas *jogador, int unity_control, int reverse_border);

void movimento_cavalo(pecas *jogador , int unity_control, int reverse_border);

pecas *allocar_memoria(int quantidade);

void movimentopecas(pecas *jogador, int unity_control, int reverse_border);

void setpecas(pecas *jogador,int quant_pecas,int time);

int pos_ocupada(pecas *jogador1, pecas *jogador2, int quant_pecas, int unity_control, int px, int py);

void loop_movimento(int quant_pecas,int *unity_control);

#endif