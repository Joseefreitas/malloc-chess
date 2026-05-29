#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <string.h>
#include <math.h>
#include "functions/constants.h"
#include "functions/math_game.h"
#include "functions/pecas.h"
#include "functions/utilis.h"
#include "functions/tabuleiro.h"
#include "functions/placar.h"
#include "functions/funcoes_placar.h"
#include "functions/funcoes_salvar_pontuacao.h"
#define power2(A) ((A)*(A))

int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "malloc(draughts): teste 1.7.8.9");
        
    Image main_image = LoadImage("/home/devcontainers/dev/Pif_Jogo/teste.png"); 
    pecas *jogador1 = allocar_memoria(quant_pecasj1);

    setpecas(jogador1,1,quant_pecasj1);
    pecas *jogador2 = allocar_memoria(quant_pecasj2);
    setpecas(jogador2,-1,quant_pecasj2);
    
    int control1 =num_textures;
    int control2=num_textures;
    int contador_turnos=0;
    int contador_movimentoj1=0;
    int contador_movimentosj2=0;
    float timer = min_timer;
    
    placar *placar_jogo1;
    placar *placar_jogo2;
    iniciar_placar(&placar_jogo1,quant_pecasj1);
    iniciar_placar(&placar_jogo2,quant_pecasj2);
    char pontuacoes_salvas[quant_pecasj1][linhas_placar];
    memset(pontuacoes_salvas,0,sizeof(pontuacoes_salvas));
    adicionar_lista(&placar_jogo1,pecas_vivasj2);
    adicionar_lista(&placar_jogo2,pecas_vivasj1);
    UnloadImage(main_image);
    
    int time_jogando = 1; 
    InitAudioDevice();
    
    Music musica_tema =  LoadMusicStream("/home/devcontainers/dev/Pif_Jogo/assets/music/bensound-glitchtones (1).mp3");
    float volume = 0.6f;
    PlayMusicStream(musica_tema);
    
    SetMusicVolume(musica_tema, volume);
    SetTargetFPS(fps);              
    
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()){    
        Jogar(&iniciar);
        if (iniciar){
        // Update 
            timer +=GetFrameTime();            
            UpdateMusicStream(musica_tema);

            if (time_jogando!= -1)
                loop_movimento(&control1,quant_pecasj1); 
            else
                loop_movimento(&control2,quant_pecasj2);

            if (timer> max_timer|| IsKeyPressed(KEY_T)){
                contador_turnos++;
                time_jogando = -(time_jogando);
                timer = min_timer;
                
            }
            Vector2 coordenadas_peca={jogador1[control1].px,jogador1[control1].py};
            Vector2 coordenadas_peca2={jogador2[control2].px,jogador2[control2].py};
        
        //----------------------------------------------------------------------------------
            float reverse_boundary = 1.0;
            if (time_jogando == 1){
                if (fora_barreiras(coordenadas_peca.x, coordenadas_peca.y, barreiras))
                    reverse_boundary = -1.0;
                jogador1[control1].isDame = virar_rainha(jogador1,control1,barreiras);
                pecas_vivasj2+=ataque_pecas(jogador1,jogador2,control1,quant_pecasj1,time_jogando);
                adicionar_lista(&placar_jogo1,pecas_vivasj2);

                if (desabilitar_peca(jogador1,control1)){
                    barrar_posicao(jogador1, control1, barreiras);
                    if (contador_movimentoj1<jogador1[control1].isDame)
                        contador_movimentoj1 += movimentopecas(jogador1,control1,reverse_boundary,jogador1[control1].isDame);
                }
                contador_movimentosj2=0;
                colisao_pecas(jogador1,jogador2,coordenadas_peca,control1,quant_pecasj1);
            }else{
                if (fora_barreiras(coordenadas_peca2.x, coordenadas_peca2.y, barreiras))
                    reverse_boundary = -1.0;
                jogador2[control2].isDame = virar_rainha(jogador2,control2,barreiras);
                pecas_vivasj1+=ataque_pecas(jogador2,jogador1,control2,quant_pecasj2,time_jogando);
                adicionar_lista(&placar_jogo2,pecas_vivasj1);

                if(desabilitar_peca(jogador2,control2)){
                    barrar_posicao(jogador2, control2, barreiras);
                    if (contador_movimentosj2<jogador2[control2].isDame)
                        contador_movimentosj2+=  movimentopecas(jogador2,control2,reverse_boundary,jogador2[control2].isDame);
                    
                }
                contador_movimentoj1=0;
                colisao_pecas(jogador2,jogador1,coordenadas_peca2,control2,quant_pecasj2);
            }       
            if (pecas_vivasj1==quant_pecasj1 || pecas_vivasj2==quant_pecasj2){
                Vector2 perdas = {quant_pecasj1-pecas_vivasj1,quant_pecasj2-pecas_vivasj2};
                vencedor(jogador1,jogador2,perdas,&placar_jogo1,&placar_jogo2,&iniciar);
                mostrar_texto_arquivo("Pif_Jogo-pontuacoes.txt",quant_pecasj2,linhas_placar,pontuacoes_salvas);
            }    
        }
            
       
        //----------------------------------------------------------------------------------
        
        // Draw
        BeginDrawing();
        
        ClearBackground(RAYWHITE);            
            if (iniciar==1.0){
                desenhar_tabuleiro();
                for(int u_c = 0;u_c<quant_pecasj1;u_c++){
                    DrawRectangle(wall_distance*(jogador1[u_c].px), wall_distance*(jogador1[u_c].py),width_print,height_print,BLACK);
                    DrawText(TextFormat("%c %d",jogador1[u_c].pecas_jogador, u_c), wall_distance*jogador1[u_c].px, wall_distance*jogador1[u_c].py, height_print, WHITE);
                }
                for(int u_c2=0;u_c2<quant_pecasj2;u_c2++){
                    DrawRectangle(wall_distance*(jogador2[u_c2].px),wall_distance*(jogador2[u_c2].py),width_print,height_print,DARKGRAY);
                    DrawText(TextFormat("%c %d",jogador2[u_c2].pecas_jogador, u_c2), wall_distance*jogador2[u_c2].px, wall_distance*jogador2[u_c2].py, height_print, WHITE);
                }
                mostrar_placar(&placar_jogo1,&placar_jogo2);
                
                if (time_jogando == -1){
                    DrawText(TextFormat("Tempo: %.1f, Vez do jogador 2",timer),850,150,20,BLACK);
                    DrawText(TextFormat("Peca selecionada %d",control2),850,180,20,BLACK);

                }
                if (time_jogando == 1){
                    DrawText(TextFormat("Tempo: %.1f, Vez do jogador 1",timer),850,150,20,BLACK);
                    DrawText(TextFormat("Peca selecionada %d ",control1),850,180,20,BLACK);
                }
                
                EndDrawing();
            }else{
                if (iniciar!=0.5){
                    DrawText("Bem vindo ao Malloc(Draughts)!",21,15,30,BLACK);
                    DrawText("Versão: 1.7.8.9",21,47,20,BLACK);
                    DrawText("Aperte enter para começar o jogo",56,390,20,BLACK);
                    EndDrawing();
                }else{
                    DrawText("Fim de Jogo\nPressione Enter para salvar e ESC para encerrar",10,10,30,BLACK);
                    DrawText("Desenvolvedores: ",100,570,20,BLACK);
                    DrawText("JOSE EDUARDO BARBOSA DE FREITAS - Código, Animações e Tabuleiro",100,595,20,BLACK);  
                    DrawText("NÍCOLAS VITOR GOMES - Código ",100,615,20,BLACK);  
                    DrawText("RENATO AUGUSTO SOARES DA SILVA - Código",100,645,20,BLACK);  
                    
                    
                    DrawText("Placar (Quantas pecas de cada jogador continuaram vivas): ",300,90,20,BLACK);
                    for(int i=0;i<quant_pecasj1;i++){
                            DrawText(TextFormat("%s", pontuacoes_salvas[i]), 300,110+(20*i),20,BLACK);           
                    }
                    EndDrawing();
                }                 
            

            }
            
                       
        }
        //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(musica_tema); 
    CloseAudioDevice();   
    CloseWindow();        
    //--------------------------------------------------------------------------------------

    return 0;
}