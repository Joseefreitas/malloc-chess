#include <stdio.h>
#include <stdlib.h>
#include <raylib/raylib/src/raylib.h>
#include <utilis.h>


typedef struct{
    char pecas_jogador;
    int px;
    int py;
    int vida;
    int defesa;
    int ataque;
    int time;
    int isDama;
}pecas;

int quant_pecas = 12;


int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras){
    if  (jogador1[unity_control].py == barreiras.y || jogador1[unity_control].py == barreiras.w){
        jogador1[unity_control].pecas_jogador = 'D';
        jogador1[unity_control].vida= 200;
        jogador1[unity_control].defesa =  20;
        jogador1[unity_control].ataque  = 40;
        return 5;
    }
    return 1;
}

int pos_ocupada(pecas *jogador1, pecas *jogador2, int unity_control, int px, int py){
    for (int i = 0; i < quant_pecas; i++){
        if (i != unity_control && (jogador1[i].px -  px)> 0.03 && (jogador1[i].py - py)> 0.03)
            return 1;
        if (i != unity_control && (jogador2[i].px - px)>0.03 && (jogador2[i].py - py) > 0.03)
            return 1;
    }
    return 0;
}

void ataque_pecas(pecas *jogador, int unity_control, int reverse_border){
    if (unity_control<=7|| unity_control==12)
                jogador[unity_control].px += (1*reverse_border);
    if (unity_control==8 || unity_control==15|| unity_control==11)
                jogador[unity_control].px += (reverse_border*5);
    if (unity_control==9 || unity_control==14)
                movimento_cavalo(jogador,unity_control,reverse_border);
    if (unity_control==10 || unity_control==13){
                jogador[unity_control].px += (reverse_border*5);
                jogador[unity_control].py += (reverse_border*5);
    }
}

pecas *allocar_memoria(int quantidade){
    pecas *aux = malloc(quantidade*sizeof(pecas));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void movimentopecas(pecas *jogador, int unity_control, int reverse_border){
    if (IsKeyDown(KEY_RIGHT)){
                            jogador[unity_control].px += (reverse_border*1);
                            jogador[unity_control].py += (reverse_border*1);
                    }
    else if (IsKeyDown(KEY_LEFT)){                
                        jogador[unity_control].px -= (reverse_border*1);
                        jogador[unity_control].py -= (reverse_border*1);     
                }
    else if (IsKeyDown(KEY_UP)){
                            jogador[unity_control].px += (reverse_border*1);
                            jogador[unity_control].py -= (reverse_border*1);
                } 
    else if (IsKeyDown(KEY_DOWN)){
                            jogador[unity_control].px -= (reverse_border*1);
                            jogador[unity_control].py += (reverse_border*1);
                        }
}

void setpecas(pecas *jogador,int time, int quant_pecas){
    for(int i=0;i<quant_pecas;i++){
        if(i<quant_pecas){
            if (i<quant_pecas && i>=quant_pecas-4)
                jogador[i].pecas_jogador = 'R';
            else{
                jogador[i].pecas_jogador = ((i>=0 && i<=3)?  'E': 'N');
            }
            jogador[i].vida= 100;
            jogador[i].defesa =  5;
            jogador[i].ataque  = 20;
        }
        jogador[i].px = (25) * ((i<=(quant_pecas/2)-1) ? i+1 : i-((quant_pecas/2)-1));
        if (time ==1)
            jogador[i].py = (10) * (((i<=(quant_pecas/2)-1)? 1 : 0));
        else
            jogador[i].py = (30) * (((i<=(quant_pecas/2)-1)? 2 : 2.5));
        jogador[i].time = time;
    }
}

void colisao_pecas(pecas *jogador1, pecas *jogador2,int unity_control, Vector2 dados_anteriores){
    if (dados_anteriores.x!= jogador1[unity_control].px && jogador1[unity_control].py!= dados_anteriores.y){
        if((pos_ocupada(jogador1, jogador2, unity_control, jogador1[unity_control].px, jogador1[unity_control].py) ) ){
            jogador1[unity_control].px = dados_anteriores.x;
            jogador1[unity_control].py = dados_anteriores.y;
        }
    }
}

void loop_movimento(int *unity_control){
    for (int i=0x0;i<quant_pecas;i++){
        if ((IsKeyDown(KEY_ZERO+i)) )
                    *unity_control = i;
        if (i<2 &&(IsKeyDown(KEY_A+i)))
                    *unity_control = (10+i);
    }
}