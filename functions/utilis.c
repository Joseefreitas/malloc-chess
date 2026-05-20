#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pecas.h"
#include <utilis.h>
#include "math_game.h"
    
const int wall_distance = 5;

void Jogar(int * valor){
    if (IsKeyPressed(KEY_ENTER))
        *valor = 1;
}

int pos_ocupada(pecas *jogador1, pecas *jogador2,int unity_control, int quant_pecas, int i){
    Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador2[i].px,jogador2[i].py};    
    float valor = distance_2_points(jogadores_coord);
    if (valor<=7)
            return 1;
    else
            return 0;
}       

int desabilitar_peca(pecas *jogador,int posicao){
    if (jogador[posicao].vida == 0)
            return 0;
    return 1;
}

int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras){
    /*const int table_max_x = 150, table_min_x = 23,table_max_y = 77, table_min_y = 0;
    const Vector4 barreiras = {table_max_x,table_max_y,table_min_x,table_min_y};*/
//        if  (jogador1[unity_control].py > barreiras.y || jogador1[unity_control].py < barreiras.w){
//     const Vector4 barreiras = {table_min_x, table_max_x, table_min_y, table_max_y};


    if (jogador1[unity_control].py >= barreiras.w || jogador1[unity_control].py <= barreiras.z){
        if (IsKeyDown(KEY_R)){
            jogador1[unity_control].pecas_jogador = 'D';
            jogador1[unity_control].vida = jogador1[unity_control].vida * 2;
            jogador1[unity_control].isDame = 2;
        }
        return jogador1[unity_control].isDame;
    }
    return jogador1[unity_control].isDame;
}

int fora_barreiras(float px, float py, Vector4 barreiras){
    if (px < barreiras.x || px > barreiras.y || py < barreiras.z || py > barreiras.w)
        return 1;
    return 0;
}

void barrar_posicao(pecas *jogador, int unity_control, Vector4 barreiras){
    if (jogador[unity_control].px < barreiras.x) jogador[unity_control].px = barreiras.x;
    if (jogador[unity_control].px > barreiras.y) jogador[unity_control].px = barreiras.y;
    if (jogador[unity_control].py < barreiras.z) jogador[unity_control].py = barreiras.z;
    if (jogador[unity_control].py > barreiras.w) jogador[unity_control].py = barreiras.w;
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

int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
   
    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};   
    int alvo = -1;
    float menor_distancia = 0.25f * (float)wall_distance;
    Vector2 atacante = {jogador1[unity_control].px, jogador1[unity_control].py};
    for(int i = 0; i < quant_pecas; i++){
        if (jogador2[i].vida > 0){
            Vector4 distancia_matar = {jogador2[i].px, jogador2[i].py, posic_mouse_convertida.x, posic_mouse_convertida.y};
            float clique_alvo = distance_2_points(distancia_matar);
            if (clique_alvo<menor_distancia){          
                Vector4 jogadores = {atacante.x,atacante.y,jogador2[i].px,jogador2[i].py};
                if(distance_2_points(jogadores)<= 10.5){
                    alvo = i;
                    menor_distancia = distance_2_points(jogadores);
                }
            }
        }
    }
    if(alvo != -1){
        //DrawText("Possivel atacar",30,BLACK);
        if(jogador1[unity_control].px-jogador2[alvo].px<6.8 && jogador1[unity_control].py-jogador2[alvo].py<6.8){
            jogador2[alvo].px = -99;
            jogador2[alvo].py = -99;
            jogador2[alvo].vida = 0;
            jogador2[alvo].pecas_jogador = 'X';
            return 1;
        }
    }
    return 0;
}

int ataque_pecas(pecas *jogador1, pecas*jogador2, int unity_control, int quant_pecas, int time_jogando){
    Vector2 posicao = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
       ((posicao.x) != ((float)wall_distance*jogador1[unity_control].px) && 
        posicao.y != ((float)wall_distance*jogador1[unity_control].py))){
        
        DrawText(TextFormat("Tentativa de ataque em: x= %.1f, y=%.1f", 
                 posicao.x/(float)wall_distance, posicao.y/(float)wall_distance), 
                 10, 190, 15, BLACK);
        int morto = matar_peca(posicao, jogador1, jogador2, unity_control, quant_pecas);
        return morto;
    }
    return 0;
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

void colisao_pecas(pecas *jogador1, pecas *jogador2,Vector2 dados_anteriores,int unity_control,int quant_pecas){
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

void liberar_pecas(pecas* jogador){
    free(jogador);
}


void vencedor(pecas *jogador1, pecas *jogador2, int quant_pecas1,Vector2 perdas){
    if ((perdas.x>=0 && perdas.x<quant_pecas1) && perdas.y!=0){
        DrawText(TextFormat("Jogador2 venceu!"),50,50,90,BLACK);
    }else if ((perdas.y>=0 && perdas.y<quant_pecas1) && perdas.x!=0){
        DrawText(TextFormat("Jogador1 venceu!"),50,50,90,BLACK);
    }else{
        DrawText(TextFormat("Empate!"),50,25,90,BLACK);
    }
    liberar_pecas(jogador1);
    liberar_pecas(jogador2);
    DrawText(TextFormat("Pressione ESC para salvar e encerrar"),90,25,30,BLACK);

}

