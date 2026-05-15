#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include <math.h>

#include "functions/math_game.h"
#include "functions/pecas.h"
#include "functions/utilis.h"
//#include "functions/placar.h"
//#include "functions/funcoes_placar.h"
#define power2(A) ((A)*(A))

int main(void){
    //ChangeDirectory(GetApplicationDirectory());
    // Initialization
    //--------------------------------------------------------------------------------------
   
    const int screenWidth = 1200;
    const int screenHeight = 850;
    const int max_speed_x = 5;
    const int max_speed_y = 5;
    const int width_print = 60;
    const int quant_pecas = 0xC;
    const int height_print = 20;
    const int wall_distance = 5;
    const int vida =100;
    const int fps = 60;
    const int num_textures = 0;
    const int table_max_x = 150, table_min_x = 23,table_max_y = 77, table_min_y = 0;
    const Vector4 barreiras = {table_max_x,table_max_y,table_min_x,table_min_y};
    InitWindow(screenWidth, screenHeight, "malloc(draughts): teste 1.7.7.3");
    
    
    Image main_image = LoadImage("/home/devcontainers/dev/Pif_Jogo/teste.png"); 
    pecas *jogador1 = allocar_memoria(quant_pecas);
    //Image table= {"/home/devcontainers/dev/Pif_Jogo/00_2c5cd.webp",screenWidth,screenHeight,1,"RGB"};
    setpecas(jogador1,1,quant_pecas);
    pecas *jogador2 = allocar_memoria(quant_pecas);
    setpecas(jogador2,-1,quant_pecas);
    int control1 =num_textures;
    int control2=num_textures;
    /*placar *placar_j1;
    placar *placar_j2;
    
    iniciar_placar(&placar_j1,quant_pecas,jogador1);
    iniciar_placar(&placar_j2,quant_pecas,jogador2);
    */
    UnloadImage(main_image);
    
    Texture tabuleiro[num_textures]= {};
    tabuleiro[num_textures] = LoadTextureFromImage(main_image);
    
    int time_jogando = 1;
             
    
    SetTargetFPS(fps);               
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()){ 
            // Update

            if (time_jogando!= -1)
                loop_movimento(&control1,quant_pecas); 
            else
                loop_movimento(&control2,quant_pecas);

            if (IsKeyDown(KEY_T))
                time_jogando = -(time_jogando);
            
            Vector2 coordenadas_peca={jogador1[control1].px,jogador1[control1].py};
            Vector2 coordenadas_peca2={jogador2[control2].px,jogador2[control2].py};
           

        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        
                /* Definr os limites de movimento, de forma manual para as peças aqui*/
        // Make sure Box B does not go out of move area limits
                     
            int reverse_boundary = 1;
            if (time_jogando == 1){
                if (((coordenadas_peca.x) < table_min_x || (coordenadas_peca.x > table_max_x))  ||  (((coordenadas_peca.y < table_min_y) || (coordenadas_peca.y) > table_max_y)) ) 
                    reverse_boundary = -1;
                movimentopecas(jogador1,control1,reverse_boundary,jogador1[control1].isDame);
                jogador1[control1].isDame = virar_rainha(jogador1,control1,barreiras);
                ataque_pecas(jogador1,jogador2,control1,quant_pecas);
                /*typedef struct{
                    pecas *player1; 
                    pecas *player2; 
                    
                    or vector3 -coordpecas,cntrl e pecasquant
                    
                    Vector2 *coordenadas_peca; 
                    int *control;
                    int *pecas_qnt;
                }context;
                context cx1 = {&jogador1[control1],&jogador2, &coordenadas_peca,&control1,&quant_pecas};

                //colisao_pecas(cx1);
                */
                colisao_pecas(jogador1,jogador2,coordenadas_peca,control1,quant_pecas);

            }
            else{
                if (((coordenadas_peca2.x) <  table_min_x || (coordenadas_peca2.x > table_max_x)) || ((coordenadas_peca2.y) < table_min_y || (coordenadas_peca2.y > table_max_y)) )
                    reverse_boundary = -1;
                movimentopecas(jogador2,control2,reverse_boundary,jogador2[control2].isDame);
                jogador2[control2].isDame = virar_rainha(jogador2,control2,barreiras);
                ataque_pecas(jogador2,jogador1,control2,quant_pecas);
                colisao_pecas(jogador2,jogador1,coordenadas_peca2,control2,quant_pecas);

                }           
            
        //}
        //----------------------------------------------------------------------------------
        
        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(tabuleiro[num_textures], table_max_x, table_min_y , BLACK);
            
            for(int u_c = 0;u_c<quant_pecas;u_c++){
                DrawRectangle(wall_distance*(jogador1[u_c].px), wall_distance*(jogador1[u_c].py),width_print,height_print,BLACK);
                DrawText(TextFormat("%c %d",jogador1[u_c].pecas_jogador, u_c), wall_distance*jogador1[u_c].px, wall_distance*jogador1[u_c].py, height_print, WHITE);
            }
            for(int u_c2=0;u_c2<quant_pecas;u_c2++){
                DrawRectangle(wall_distance*(jogador2[u_c2].px),wall_distance*(jogador2[u_c2].py),width_print,height_print,DARKGRAY);
                DrawText(TextFormat("%c %d",jogador2[u_c2].pecas_jogador, u_c2), wall_distance*jogador2[u_c2].px, wall_distance*jogador2[u_c2].py, height_print, WHITE);
            }
            
            DrawText("Digite a peça que você quer, depois use o teclado para mover. Selecione T para dar a vez ao outro jogador", 0, 30, 15, BLACK);

            DrawText(TextFormat("Peca %d: time: %d, x= %.1f, y=%.1f",control1,1,jogador1[control1].px,jogador1[control1].py),0,90,15,BLACK);
            if (time_jogando == -1)
                DrawText("Jogador 2!",0,290,15,BLACK);
            if (time_jogando == 1)
                DrawText("Jogador 1!",0,290,15,BLACK);

            DrawText(TextFormat("Peca %d: time: %d, x= %.1f, y=%.1f",control2,-1,jogador2[control2].px,jogador2[control2].py),0,150,15,BLACK);
            EndDrawing();
        //----------------------------------------------------------------------------------
        }   
        //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(tabuleiro[num_textures]);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}