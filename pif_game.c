#include<stdio.h>
#include <stdlib.h>
#include "include/raylib/src/raylib.h"

// para compilar:  gcc pif_game.c -o pif_game -Iinclude/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./pif_game
/* pros outros é mais fácil. posso isolar o moviento do cavalo. numa função
    P = peao
    r = rei
    R =rainha
    T=torre
    B=bispo
    C=cavalo*/
    
typedef struct{
    char pecas_jogador;
    int px;
    int py;
    int vida;
    int defesa;
    int ataque;
    int time;
}pecas;

int quant_pecas = 16;

 void movimento_cavalo(pecas *jogador , int unity_control){
    if (IsKeyDown(KEY_RIGHT)){    
        jogador[unity_control].px -= 3;
        jogador[unity_control].py += 2;
    }
    if (IsKeyDown(KEY_DOWN)){
        jogador[unity_control].px -= 3;
        jogador[unity_control].py -= 2;
    }
    if (IsKeyDown(KEY_UP)){
        jogador[unity_control].py += 3;
        jogador[unity_control].px += 2;
        
    }
    if (IsKeyDown(KEY_LEFT)){
        jogador[unity_control].px += 3;
        jogador[unity_control].py += 2;
    }
}

pecas *allocar_memoria(int quantidade){
    pecas *aux = malloc(quantidade*sizeof(pecas));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void movimentopecas(pecas *jogador, int unity_control){
    if (IsKeyDown(KEY_RIGHT)){
                    if (unity_control<=7|| unity_control==12)
                        jogador[unity_control].px += 1;
                    if (unity_control==8 || unity_control==15|| unity_control==11)
                        jogador[unity_control].px += 5;
                    if (unity_control==9 || unity_control==14)
                        movimento_cavalo(jogador,unity_control);
                    if (unity_control==10 || unity_control==13){
                            jogador[unity_control].px += 5;
                            jogador[unity_control].py += 5;
                    }
                }
    else if (IsKeyDown(KEY_LEFT)){
                    if (unity_control<=7 || unity_control==12)
                        jogador[unity_control].px -= 1;
                    if (unity_control==8 || unity_control==15 || unity_control==11)
                        jogador[unity_control].px -= 5;
                    if (unity_control==9 || unity_control==14)
                        movimento_cavalo(jogador,unity_control);
                    if (unity_control==10 || unity_control==13){
                        jogador[unity_control].px -= 5;
                        jogador[unity_control].py -= 5;
                    }
                }
    else if (IsKeyDown(KEY_UP)){
                    if (unity_control<=7|| unity_control==12)
                        jogador[unity_control].py -= 1;
                    if (unity_control==8 || unity_control==15|| unity_control==11)
                        jogador[unity_control].py -= 5;
                    if (unity_control==9 || unity_control==14)
                        movimento_cavalo(jogador,unity_control);
                    if (unity_control==10 || unity_control==13){
                            jogador[unity_control].px += 5;
                            jogador[unity_control].py -= 5;
                    }
                } 
    else if (IsKeyDown(KEY_DOWN)){
                    if (unity_control<=7|| unity_control==12)
                        jogador[unity_control].py += 1;
                    if (unity_control==9 || unity_control==14)
                        movimento_cavalo(jogador,unity_control);
                    if (unity_control==8 || unity_control==15|| unity_control==11)
                        jogador[unity_control].py += 5;
                    if (unity_control==10 || unity_control==13){
                            jogador[unity_control].px -= 5;
                            jogador[unity_control].py += 5;
                        }
                    }
}

void setpecas(pecas *jogador,int quant_pecas,int time){
    for(int i=0;i<quant_pecas;i++){
        if(i<=7){
            jogador[i].pecas_jogador = 'P';
            jogador[i].vida= 100;
            jogador[i].defesa =  5;
            jogador[i].ataque  = 20;
        }
        if (i==8 || i==15){
            jogador[i].pecas_jogador= 'T';
            jogador[i].vida = 250;
            jogador[i].defesa = 20;
            jogador[i].ataque  = 50;
        }
        if (i==10 || i==13){
            jogador[i].pecas_jogador='B';
            jogador[i].vida = 80;
            jogador[i].defesa = 17;
            jogador[i].ataque  = 45;
        }
        if (i==11){
            jogador[i].pecas_jogador = 'R';
            jogador[i].vida = 180;
            jogador[i].defesa = 10;
            jogador[i].ataque  = 75;
        }
        if (i==12){
            jogador[i].pecas_jogador = 'r';
            jogador[i].vida = 350;
            jogador[i].defesa = 15;
            jogador[i].ataque  = 10;
        }
        if (i==9 || i==14){
            jogador[i].pecas_jogador = 'C';
            jogador[i].vida = 150;
            jogador[i].defesa = 10;
            jogador[i].ataque  = 35;
        }
        jogador[i].px = (25) * ((i<=7) ? i+1 : i-7);
         if (time ==1)
            jogador[i].py = (10) * (((i<=7)? 1 : 0));
        else
            jogador[i].py = (30) * (((i<=7)? 2 : 2.5));
        jogador[i].time = 1;
    }
}



/*
J1:
0 - 25,10
1 - 50,10
2 - 75,10
3 - 100,10
4 - ...,10
5 - ...,10
6 - ...,10
7 - ...,10
8 - 25,0
9 - 50,0
10 - ...
11 - ...
12 - ...
13 - ...
14 - ...
15 - ...


(8 - 7) * -25 = -8*25 +25*7  
J2:
0 - -25,-10
1 - -50,-10
2 - -...
3 - ...
4 - ...
5 - ... 
6 - ... 
7 - ...
8 - -25,0
9 -
10 -
11 -
12 -
13 -
14 -
15 -


*/



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 850;
    const int quant_pecas = 0x10;
    const int max_speed_x = 5;
    const int max_speed_y =5;

    InitWindow(screenWidth, screenHeight, "malloc(chess): teste 1.5.3");
    pecas *jogador1 = allocar_memoria(quant_pecas);
    setpecas(jogador1,quant_pecas,1);
    pecas *jogador2 = allocar_memoria(quant_pecas);
    setpecas(jogador2,quant_pecas,-1);
    int unity_control = 0;
    Vector2 matriz_jogo = {5*(float)jogador1[quant_pecas/2].px, 5*(float) jogador2[quant_pecas-1].py/2};
    int time_jogando = 1 ;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    { 
        
        for(int u_c = 0;u_c<quant_pecas;u_c++){
                DrawRectangle(5*(jogador1[u_c].px), 5*(jogador1[u_c].py),60,20,BLACK);
                DrawText(TextFormat("%c %d",jogador1[u_c].pecas_jogador, u_c), 5*jogador1[u_c].px, 5*jogador1[u_c].py, 20, WHITE);
        }
        for(int u_c2=0;u_c2<quant_pecas;u_c2++){
                DrawRectangle(5*(jogador2[u_c2].px), 5*(jogador2[u_c2].py),60,20,GRAY);
                DrawText(TextFormat("%c %d",jogador2[u_c2].pecas_jogador, u_c2), 5*jogador2[u_c2].px, 5*jogador2[u_c2].py, 20, WHITE);
        }
        
        DrawRectangleLines(matriz_jogo.x,matriz_jogo.y,290,290,BLACK);
            // Update
            for (int i=0x0;i<quant_pecas;i++){
                int aux = IsKeyDown(KEY_ZERO);
                if (aux == 0 && i<=0x9 && (IsKeyDown(KEY_ZERO+i)) )
                    unity_control = i;
                if (aux==1 && (IsKeyDown(KEY_ZERO+i)))
                    unity_control = (10+i);
            }
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
            if (time_jogando == 1){
                movimentopecas(jogador1,unity_control);
            }
            else{
                movimentopecas(jogador2,unity_control);
            }
        //----------------------------------------------------------------------------------
        
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Digite a peça que você quer, depois use o teclado para mover. Selecione T para dar a vez ao outro jogador", 0, 30, 15, BLACK);
            if (IsKeyDown(KEY_T))
                time_jogando*=-1;

            EndDrawing();
        //----------------------------------------------------------------------------------
        }   
        //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}