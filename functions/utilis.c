#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pecas.h"
#include <utilis.h>
#include "math_game.h"
    
 const int wall_distance = 5;

int pos_ocupada(pecas *jogador1, pecas *jogador2,int unity_control, int quant_pecas, int i){
    Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador2[i].px,jogador2[i].py};    
    float valor = distance_2_points(jogadores_coord);
    if (valor<=7)
            return 1;
    else
            return 0;
}       

int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras){
    if  (jogador1[unity_control].py > barreiras.y || jogador1[unity_control].py < barreiras.w){
        jogador1[unity_control].pecas_jogador = 'D';
        jogador1[unity_control].vida= 2*(jogador1[unity_control].vida);
        jogador1[unity_control].isDame+= jogador1[unity_control].isDame;
        /*jogador1[unity_control].defesa =  20;
        jogador1[unity_control].ataque  = 40;*/
        return 2;
    }
    return 1;
}

pecas *allocar_memoria(int quantidade){
    pecas *aux = malloc(quantidade*sizeof(pecas));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void movimentopecas(pecas *jogador, int unity_control, int reverse_border, int IsDame){
    if (IsKeyDown(KEY_RIGHT)){
                            jogador[unity_control].px += (reverse_border*IsDame);
                            jogador[unity_control].py += (reverse_border*IsDame);
                    }
    else if (IsKeyDown(KEY_LEFT)){                
                        jogador[unity_control].px -= (reverse_border*IsDame);
                        jogador[unity_control].py -= (reverse_border*IsDame);     
                }
    else if (IsKeyDown(KEY_UP)){
                            jogador[unity_control].px += (reverse_border*IsDame);
                            jogador[unity_control].py -= (reverse_border*IsDame);
                } 
    else if (IsKeyDown(KEY_DOWN)){
                            jogador[unity_control].px -= (reverse_border*IsDame);
                            jogador[unity_control].py += (reverse_border*IsDame);
                        }
}

void matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};   
    
    // Procura a peça inimiga mais próxima da posição do mouse
    int alvo_index = -1;
    float menor_distancia = 0.125 * (float)wall_distance;
    
    for(int i = 0; i < quant_pecas; i++){
        if (jogador2[i].vida > 0){
            Vector4 distancia_matar = {jogador2[i].px, jogador2[i].py, posic_mouse_convertida.x, posic_mouse_convertida.y};
            float dist = distance_2_points(distancia_matar);
            if(dist < menor_distancia){
                alvo_index = i;
                menor_distancia = dist;
            }
        }
    }
    
    if(alvo_index != -1){
        float atacante_x = jogador1[unity_control].px;
        float atacante_y = jogador1[unity_control].py;
        float alvo_x = jogador2[alvo_index].px;
        float alvo_y = jogador2[alvo_index].py;
        
        // Valida se está no mesmo eixo X ou Y (ataque em linha reta)
        int mesmo_eixo_x = (atacante_x -alvo_x<2.8);
        int mesmo_eixo_y = (atacante_y - alvo_y<2.8);
        
        if(mesmo_eixo_x || mesmo_eixo_y){
            // Mata a peça
            jogador2[alvo_index].px = -99;
            jogador2[alvo_index].py = -99;
            jogador2[alvo_index].vida = 0;
            jogador2[alvo_index].pecas_jogador = 'X';
        }
    }
}
//so posso permitir 1 ataque per turno. mas, pela algoritmo, ainda é possível afetar mais de uma. mas tá bem melhor agora

void ataque_pecas(pecas *jogador1, pecas*jogador2, int unity_control, int quant_pecas){
    Vector2 posicao_mouse = GetMousePosition();
    // Valida se o clique não está na mesma posição da peça
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
       ((posicao_mouse.x) != ((float)wall_distance*jogador1[unity_control].px) && 
        posicao_mouse.y != ((float)wall_distance*jogador1[unity_control].py))){
        
        DrawText(TextFormat("Tentativa de ataque em: x= %.1f, y=%.1f", 
                 posicao_mouse.x/(float)wall_distance, posicao_mouse.y/(float)wall_distance), 
                 10, 190, 15, BLACK);
        matar_peca(posicao_mouse, jogador1, jogador2, unity_control, quant_pecas);
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
            /*jogador[i].defesa =  5;
            jogador[i].ataque  = 20;*/
        }
        jogador[i].px = (25) * ((i<=(quant_pecas/2)-1) ? i+1 : i-((quant_pecas/2)-1));
        if (time ==1)
            jogador[i].py = (10) * (((i<=(quant_pecas/2)-1)? 1 : 0));
        else
            jogador[i].py = (30) * (((i<=(quant_pecas/2)-1)? 2 : 2.5));
        jogador[i].time = time;
        jogador[i].isDame=1;
    }
}

void colisao_pecas(pecas *jogador1, pecas *jogador2,Vector2 dados_anteriores,int unity_control,int quant_pecas ){
    for(int i = 0;i<quant_pecas;i++){ 
        if((pos_ocupada(jogador1, jogador2, unity_control,quant_pecas,i)) ){
            jogador1[unity_control].px = dados_anteriores.x;
            jogador1[unity_control].py = dados_anteriores.y;
        }
    } 
}

void loop_movimento(int *unity_control, int quant_pecas){
    for (int i=0x0;i<quant_pecas;i++){
        if ((IsKeyDown(KEY_ZERO+i)))
                    *unity_control = i;
        if (i<2 &&(IsKeyDown(KEY_A+i)))
                    *unity_control = (10+i);
    }
}