#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"
#include "pecas.h"
#include "utilis.h"
#include "math_game.h"
#include "constants.h"
#include "placar.h"
#include "funcoes_placar.h"
#include "funcoes_salvar_pontuacao.h"

void Jogar(double * valor){
    if (IsKeyPressed(KEY_ENTER))
        *valor = 1.0;
}

int pos_ocupada(pecas *jogador1, pecas *jogador2,int unity_control, int quant_pecas, int i){
    Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador2[i].px,jogador2[i].py};    
    Vector4 jogadores_entresi = {jogador1[unity_control].px,jogador1[unity_control].py,jogador1[i].px,jogador1[i].py};    
    float valor_dif = distance_2_points(jogadores_coord);
    float valor_mesmo = distance_2_points(jogadores_entresi);
    if ((valor_mesmo>=0.3 && valor_mesmo<=9) || (valor_dif>=0.3 && valor_dif<=9))
            return 1;
    else
            return 0;
}       

int desabilitar_peca(pecas *jogador,int posicao){
    if (jogador[posicao].vida == 0)
            return 0;
    return 1;
}

int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras){    float limite = 27.0f;
    float y_conv = jogador1[unity_control].py;
    if (jogador1[unity_control].time==1){
        if ((y_conv<=barreiras.w && barreiras.w-y_conv<=limite)){
            if (IsKeyPressed(KEY_R)){
                jogador1[unity_control].pecas_jogador = 'D';
                jogador1[unity_control].vida = jogador1[unity_control].vida * 2;
                jogador1[unity_control].isDame = 2;
            }
        }
        return jogador1[unity_control].isDame;
    }else{
        if ((y_conv>=barreiras.z &&  y_conv-barreiras.z<=limite)){    
            if (IsKeyPressed(KEY_R)){
                jogador1[unity_control].pecas_jogador = 'D';
                jogador1[unity_control].vida = jogador1[unity_control].vida * 2;
                jogador1[unity_control].isDame = 2;
            }
            return jogador1[unity_control].isDame;
        }
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

int movimentopecas (pecas *jogador, int unity_control, int reverse_border,int IsDame){       
        int cont=0;
        if (IsKeyPressed(KEY_RIGHT)){
                            float px_movimento = jogador[unity_control].px + (passo*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py + (passo*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        else if (IsKeyPressed(KEY_LEFT)){   
                            float px_movimento = jogador[unity_control].px - (passo*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py - (passo*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        else if (IsKeyPressed(KEY_UP)){
                            float px_movimento = jogador[unity_control].px + (passo*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py - (passo*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        else if (IsKeyPressed(KEY_DOWN)){
                            float px_movimento = jogador[unity_control].px - (passo*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py + (passo*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        return cont;                    
       }

int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
   
    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};   
    int indice = -1;
    Vector2 atacante = {jogador1[unity_control].px, jogador1[unity_control].py};
    for(int i = 0; i < quant_pecas; i++){
        if (jogador2[i].vida > 0 && jogador1[i].vida>0){        
            Vector2 alvo = {jogador2[i].px, jogador2[i].py};

            Vector4 jogadores = {atacante.x,atacante.y,alvo.x,alvo.y};
            float dist_jog = distance_2_points(jogadores);
            if (dist_jog>=15.5 && dist_jog<60.0){
                Vector4 distancia_matar = {jogador2[i].px, jogador2[i].py, posic_mouse_convertida.x, posic_mouse_convertida.y};
                float clique_alvo = distance_2_points(distancia_matar);
                
                if((clique_alvo>=0.03 && clique_alvo<=0.7)){
                    indice = i;     
                }
                else{DrawText("Não é possível atacar",850,180,30,BLACK);}
                }
         }
    }
        if (indice!=-1){
            jogador2[indice].px = -99;
            jogador2[indice].py = -99;
            jogador2[indice].vida = 0;
            jogador2[indice].pecas_jogador = 'X';
            return 1;
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
if (iniciar!=1.0){    
    for(int i=0;i<quant_pecas;i++){
        if(i<quant_pecas){
            if (i<quant_pecas && i>=quant_pecas-4)
                jogador[i].pecas_jogador = 'R';
            else{
                jogador[i].pecas_jogador = ((i>=0 && i<=3)?  'E': 'N');
            }
            jogador[i].vida= 100;
        }
        jogador[i].px = (25.0) * ((i<=(quant_pecas/2)-1) ? i+0.54: i-((quant_pecas/2)) +0.487  );
        if (time ==1)
            jogador[i].py = (5.1) * (((i<=(quant_pecas/2)-1)? 0.5 : 8.0));
        else
            jogador[i].py = (30.0) * (((i<=(quant_pecas/2)-1)? 5.0 : 4.0));
        jogador[i].time = time;
        jogador[i].isDame=1;
        }
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
        if ((IsKeyPressed(KEY_ZERO+i)))
                    *unity_control = i;
        if (i<2 && (IsKeyDown(KEY_ZERO+i)&& IsKeyPressedRepeat(KEY_ZERO+i)))
                    *unity_control = (10+i);
    }
}

void liberar_pecas(pecas* jogador){
    free(jogador);
    jogador=NULL;   
}

void vencedor(pecas *jogador1, pecas *jogador2,Vector2 perdas,double *iniciar){
    *iniciar = 0.5;
    char resultado[90];
    if ((perdas.x>=0 && perdas.x<quant_pecasj1) && perdas.y!=0){
        strcpy(resultado," Jogador2 venceu!");
    }else if ((perdas.y>=0 && perdas.y<quant_pecasj1) && perdas.x!=0){
        strcpy(resultado," Jogador1 venceu!");
    }
    if (IsKeyPressed(KEY_ENTER)){        
        char str1[90]; 
        char texto[180] = "Jogador 1: ";
        char str3[90] = "Jogador 2: ";
        char str4[90] ;
        snprintf(str1, sizeof(str1),"%f ", perdas.x);
        snprintf(str4,sizeof(str4),"%f ",perdas.y);
        strcat(texto,str1);
        strcat(str3,str4);
        strcat(texto,str3);
        strcat(texto,resultado);
        criar_arquivo("Pif_Jogo-pontuacoes.txt");
        inserir_texto_arquivo("Pif_Jogo-pontuacoes.txt",texto);
        
    }
}

