#ifndef MEU_JOGO_H
#define MEU_JOGO_H 
#include "pecas.h"
#include "raylib.h"
#include "placar.h"

void Jogar(double *valor);

int pos_ocupada(pecas *jogador1, pecas *jogador2,int unity_control, int quant_pecas, int i);

int desabilitar_peca(pecas *jogador,int posicao);

int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras);

int fora_barreiras(float px, float py, Vector4 barreiras);

void barrar_posicao(pecas *jogador, int unity_control, Vector4 barreiras);

pecas *allocar_memoria(int quantidade);

int movimentopecas(pecas *jogador, int unity_control, int reverse_border, int IsDame);

int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas);

int ataque_pecas(pecas *jogador1, pecas*jogador2,int unity_control,int quant_pecas, int time_jogando);

void setpecas(pecas *jogador,int time, int quant_pecas);

void colisao_pecas(pecas *jogador1, pecas *jogador2,Vector2 dados_anteriores,int unity_control,int quant_pecas );

void loop_movimento(int *unity_control, int quant_pecas);

void vencedor(pecas *jogador1, pecas *jogador2,Vector2 perdas, double *iniciar);

#endif