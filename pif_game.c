#include<stdio.h>
#include <stdlib.h>
#include "include/raylib/src/raylib.h"

/*
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
    }pecas;

int quant_pecas =16;

pecas *allocar_memoria(int quantidade){
    pecas *aux = malloc(quantidade*sizeof(pecas));
    if (aux==NULL) 
        return NULL;
    return aux;
}

void setpecas(pecas *jogador){
    for(int i=0;i<quant_pecas;i++){
        if(i==0 || i==1 || i==2 || i==3 || i==4 || i==5 || i==6 || i==7 )
            jogador[i].pecas_jogador = 'P';
        if (i==8 || i==15)
            jogador[i].pecas_jogador= 'T';
        if (i==10 || i==13)
            jogador[i].pecas_jogador='B';
        if (i==11)
            jogador[i].pecas_jogador = 'R';
        if (i==12)
            jogador[i].pecas_jogador = 'r';
        if (i==9 || i==14)
            jogador[i].pecas_jogador = 'C';
        jogador[i].px = i+1;
        jogador[i].py = ((i<=7)? 1 : (0));
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}