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
//const int wall_distance = 5;

void Jogar(double * valor){
    if (IsKeyPressed(KEY_ENTER))
        *valor = 1.0;
}
/*
int pos_ocupada_mesmo_time(pecas *jogador1,int unity_control, int quant_pecas, int i){
    Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador1[i].px,jogador1[i].py};    
    float valor = distance_2_points(jogadores_coord);
    if (valor>0.5 && valor<=7)
            return 1;
    else
            return 0;
}       
*/
int pos_ocupada(pecas *jogador1, pecas *jogador2,int unity_control, int quant_pecas, int i){
    Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador2[i].px,jogador2[i].py};    
    Vector4 jogadores_entresi = {jogador1[unity_control].px,jogador1[unity_control].py,jogador1[i].px,jogador1[i].py};    
    float valor_dif = distance_2_points(jogadores_coord);
    float valor_mesmo = distance_2_points(jogadores_entresi);
    if (valor_mesmo>=0.2 && valor_mesmo<=8 || valor_dif>=0.2 && valor_dif<=8)
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
/*
const float passo_grade = 25.0f * (float)IsDame;
    Vector2 mouse = GetMousePosition();
    Vector2 origem = {jogador[unity_control].px, jogador[unity_control].py};
    Vector2 destino = {mouse.x / (float)wall_distance, mouse.y / (float)wall_distance};
    Vector2 destino_snap = {
        origem.x + roundf((destino.x - origem.x) / passo_grade) * passo_grade,
        origem.y + roundf((destino.y - origem.y) / passo_grade) * passo_grade
    };
    float delta_x = destino_snap.x - origem.x;
    float delta_y = destino_snap.y - origem.y;
    float orientacao = (reverse_border < 0) ? -1.0f : 1.0f;



    if (delta_x != 0.0f && delta_y != 0.0f && fabsf(fabsf(delta_x) - fabsf(delta_y)) <= (passo_grade * 0.1f)){
            jogador[unity_control].px = origem.x + copysignf(passo_grade, delta_x) * orientacao;
            jogador[unity_control].py = origem.y + copysignf(passo_grade, delta_y) * orientacao;
        }
        */
/**/

/*

void movimentopecas (pecas *jogador, int unity_control, int reverse_border,int IsDame){
    
    const float passo_grade = 25.0f * (float)IsDame;
    Vector2 mouse = GetMousePosition();
    Vector2 origem = {jogador[unity_control].px, jogador[unity_control].py};
    Vector2 destino = {roundf(mouse.x / (float)wall_distance), roundf(mouse.y / (float)wall_distance)};
    Vector2 destino_snap = {
        origem.x + roundf(destino.x / passo_grade) * passo_grade,
        origem.y + roundf(destino.y / passo_grade) * passo_grade
    };
    float delta_x = destino_snap.x - origem.x;
    float delta_y = destino_snap.y - origem.y;

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        if (delta_x != 0.0f && delta_y != 0.0f && fabsf(fabsf(delta_x) - fabsf(delta_y)) <= (passo_grade * 0.1f)){
            jogador[unity_control].px = origem.x + copysignf(passo_grade * (float)reverse_border, delta_x);
            jogador[unity_control].py = origem.y + copysignf(passo_grade * (float)reverse_border, delta_y);
        }
    }
}
*/
/*

void movimentopecas (pecas *jogador, int unity_control, int reverse_border,int IsDame){
    
    float passo_grade = 25.0f * (float)IsDame;
    Vector2 mov = GetMousePosition();
    Vector2 origem = {jogador[unity_control].px, jogador[unity_control].py};
    Vector2 destino = {mov.x / (float)wall_distance, mov.y / (float)wall_distance};
   
    Vector2 destino2 = {
        origem.x + roundf(destino.x / passo_grade) * passo_grade,
        origem.y + roundf(destino.y / passo_grade) * passo_grade
    };
    
    float reverse_borderx = destino2.x - origem.x;
    float reverse_bordery = destino2.y - origem.y;


    // PEra ai, eu so precios olhar se a dinstancia entre onde eu estaa e eonde eu vou é menor. pq se eu voltar, so precisa andar para tras. o ppara frente. Justamente como a ia pensou

    
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        if (reverse_borderx != 0.0f && reverse_bordery != 0.0f && fabsf(fabsf(reverse_borderx) - fabsf(reverse_bordery)) <= (passo_grade * 0.1f)){
            jogador[unity_control].px = origem.x + copysignf(passo_grade * (float)reverse_border,reverse_borderx);
            jogador[unity_control].py = origem.y + copysignf(passo_grade * (float)reverse_border,reverse_bordery);
        }
    }
}
*/

int movimentopecas (pecas *jogador, int unity_control, int reverse_border,int IsDame){       
        int cont =0;
        if (IsKeyPressed(KEY_RIGHT)){
                            float px_movimento = jogador[unity_control].px + (25.0*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py + (25.0*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        else if (IsKeyPressed(KEY_LEFT)){   
                            float px_movimento = jogador[unity_control].px - (25.0*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py - (25.0*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        else if (IsKeyPressed(KEY_UP)){
                            float px_movimento = jogador[unity_control].px + (25.0*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py - (25.0*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        else if (IsKeyPressed(KEY_DOWN)){
                            float px_movimento = jogador[unity_control].px - (25.0*reverse_border*IsDame);
                            float py_movimento = jogador[unity_control].py + (25.0*reverse_border*IsDame);
                            if (!fora_barreiras(px_movimento,py_movimento,barreiras)){
                                jogador[unity_control].px = px_movimento;
                                jogador[unity_control].py = py_movimento;
                                cont++;
                        }
                    }
        return cont;                    
       }


/*
int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
   
    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};   
    int alvo = -1;
    float menor_distancia = 0.3f * (float)wall_distance;
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
                else{DrawText("Não é possivel atacar",850,180,30,BLACK);}
            }
        }
    }
    if(alvo != -1){
        
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

*/

/*
int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
   
    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};   
    int alvo = -1;
    float menor_distancia = 0.3f * (float)wall_distance;
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
                else{DrawText("Não é possivel atacar",850,180,30,BLACK);}
            }
        }
    }
    if(alvo != -1){
        
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
*/ 
/*

int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
    float passo_casa = 25.0f;
    float tolerancia_diagonal = 12.0f;
    int eh_dama = (jogador1[unity_control].isDame > 1);
    float tolerancia_clique = 7.0f;
    int max_casas = eh_dama ? 2 : 1;
    int alvo = -1;
    float melhor_clique = tolerancia_clique + 1.0f;

    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};
    Vector2 atacante = {jogador1[unity_control].px, jogador1[unity_control].py};

    for (int i = 0; i < quant_pecas; i++){
        if (jogador2[i].vida <= 0)
            continue;

        float dx = jogador2[i].px - atacante.x;
        float dy = jogador2[i].py - atacante.y;
        float abs_dx = fabsf(dx);
        float abs_dy = fabsf(dy);

        if (fabsf(abs_dx - abs_dy) > tolerancia_diagonal)
            continue;

        int casas = (int)roundf(fmaxf(abs_dx, abs_dy) / passo_casa);
        if (casas < 1 || casas > max_casas)
            continue;

        if (!eh_dama){
            int direcao_frente = (jogador1[unity_control].time > 0) ? 1 : -1;
            if (((dy > 0.0f) ? 1 : -1) != direcao_frente)
                continue;
        }

        Vector4 distancia_matar = {jogador2[i].px, jogador2[i].py, posic_mouse_convertida.x, posic_mouse_convertida.y};
        float clique_alvo = distance_2_points(distancia_matar);
        if (clique_alvo <= tolerancia_clique && clique_alvo < melhor_clique){
            melhor_clique = clique_alvo;
            alvo = i;
        }
    }

    if (alvo == -1){
        DrawText("Não é possivel atacar",850,180,30,BLACK);
        return 0;
    }

    jogador2[alvo].px = -99.0;
    jogador2[alvo].py = -99.0;
    jogador2[alvo].vida = 0;
    jogador2[alvo].pecas_jogador = 'X';
    return 1;
}
/*/
int matar_peca(Vector2 posic_mouse, pecas *jogador1, pecas *jogador2, int unity_control, int quant_pecas){
   
    Vector2 posic_mouse_convertida = {posic_mouse.x / (float)wall_distance, posic_mouse.y / (float)wall_distance};   
    int alvo = -1;
    float menor_distancia = (float)wall_distance * (float)wall_distance;
    Vector2 atacante = {jogador1[unity_control].px, jogador1[unity_control].py};
    for(int i = 0; i < quant_pecas; i++){
        if (jogador2[i].vida > 0 && jogador1[i].vida>0){        
            Vector4 distancia_matar = {jogador2[i].px, jogador2[i].py, posic_mouse_convertida.x, posic_mouse_convertida.y};
            float clique_alvo = distance_2_points(distancia_matar);
            Vector4 jogadores = {atacante.x,atacante.y,jogador2[i].px,jogador2[i].py};
            float dist_jog = distance_2_points(jogadores);
                if(dist_jog<1.2 && clique_alvo>0 && clique_alvo<=2.0){
                    jogador2[i].px = -99;
                    jogador2[i].py = -99;
                    jogador2[i].vida = 0;
                    jogador2[i].pecas_jogador = 'X';
                    return 1;
                }
                else{DrawText("Não é possivel atacar",850,180,30,BLACK);}
            }
        }
    return 0;
    }

   
/**/

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

/**/

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
            /*jogador[i].defesa =  5;
            jogador[i].ataque  = 20;*/
        }
        jogador[i].px = (25.0) * ((i<=(quant_pecas/2)-1) ? i+0.55: i-((quant_pecas/2)) +0.487  );
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
        if( /*(pos_ocupada_mesmo_time(jogador1, unity_control,quant_pecas,i)) ||*/ (pos_ocupada(jogador1, jogador2, unity_control,quant_pecas,i)) ){
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

void vencedor(pecas *jogador1, pecas *jogador2,Vector2 perdas, placar **head1,placar **head2,double *iniciar){
    *iniciar = 0.5;
    char resultado[90];
    if ((perdas.x>=0 && perdas.x<quant_pecasj1) && perdas.y!=0){
        strcpy(resultado," Jogador1 venceu!");
    }else if ((perdas.y>=0 && perdas.y<quant_pecasj1) && perdas.x!=0){
        strcpy(resultado," Jogador2 venceu!");
    }
    //DrawText(TextFormat("%s",resultado),850,350,30,BLACK);
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
        
        /*liberar_pecas(jogador1);
        liberar_pecas(jogador2);
        liberar_placar(head1,head2);
        */
        //CloseWindow();
    }
}

