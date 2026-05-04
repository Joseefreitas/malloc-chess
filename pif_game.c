#include<stdio.h>
#include <stdlib.h>
#include "raylib/raylib/src/raylib.h"
#include <math.h>
//#include <functions/utilis.h>

#include "raylib/raylib/src/raudio.c"
#define power2(A) ((A)*(A))
  
typedef struct{
    char pecas_jogador;
    int px;
    int py;
    int vida;
    int defesa;
    int ataque;
    int time;
    int isDame;
}pecas;
//77 max y
// 0 min y


int distance_2_points(Vector4 jogadores_coordenadas){
    return (sqrt(power2(jogadores_coordenadas.x-jogadores_coordenadas.z) + power2(jogadores_coordenadas.y-jogadores_coordenadas.w)));
}

int pos_ocupada(pecas *jogador1, pecas *jogador2,int unity_control, int quant_pecas, int i){
    Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador2[i].px,jogador2[i].py};    
    int valor = distance_2_points(jogadores_coord);
    if (valor<=7)
            return 1;
    else
            return 0;
}
       

int virar_rainha(pecas *jogador1,int unity_control, Vector4 barreiras){
    if  (jogador1[unity_control].py > barreiras.y || jogador1[unity_control].py < barreiras.w){
        jogador1[unity_control].pecas_jogador = 'D';
        jogador1[unity_control].vida= 200;
        jogador1[unity_control].defesa =  20;
        jogador1[unity_control].ataque  = 40;
        return 2;
    }
    return 1;
}

/*
void ataque_pecas(pecas *jogador1, int unity_control, int reverse_border){
    int dx[] = {-1, 1, -1, 1};
    int dy[] = {-1, -1, 1, 1};
    
    Vector2 AttackPosition = GetMousePosition();
    Vector4 jogadores_ataque = {jogador1[unity_control].px,jogador1[unity_control].py,AttackPosition.x,AttackPosition.y};
    

    



   }
*/

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
        jogador[i].isDame=1;
    }
}




void colisao_pecas(pecas *jogador1, pecas *jogador2,Vector2 dados_anteriores,int unity_control,int quant_pecas ){
    
    for(int i = 0;i<quant_pecas;i++){ 
        if((pos_ocupada(jogador1, jogador2, unity_control,quant_pecas,i))){
            jogador1[unity_control].px = dados_anteriores.x;
            jogador1[unity_control].py = dados_anteriores.y;
        }
    }
   
}


void loop_movimento(int *unity_control, int quant_pecas){
    for (int i=0x0;i<quant_pecas;i++){
        if ((IsKeyDown(KEY_ZERO+i)) )
                    *unity_control = i;
        if (i<2 &&(IsKeyDown(KEY_A+i)))
                    *unity_control = (10+i);
    }
}

int main(void){
    ChangeDirectory(GetApplicationDirectory());
    // Initialization
    //--------------------------------------------------------------------------------------
    
    const int screenWidth = 1200;
    const int screenHeight = 850;
    const int max_speed_x = 5;
    const int max_speed_y = 5;
    const int width_print = 60;
    const int quant_pecas = 0xC;
    const int height_print = 20;
    const int table_max_x = 150, table_min_x = 23,table_max_y = 77, table_min_y = 0;
 
    
    //Image table= {"/home/devcontainers/dev/Pif_Jogo/00_2c5cd.webp",screenWidth,screenHeight,1,"RGB"};
    InitWindow(screenWidth, screenHeight, "malloc(draughts): teste 1.7.7.2");
    pecas *jogador1 = allocar_memoria(quant_pecas);
    setpecas(jogador1,1,quant_pecas);
    Vector4 barreiras = {table_max_x,table_max_y,table_min_x,table_min_y};
    pecas *jogador2 = allocar_memoria(quant_pecas);
    setpecas(jogador2,-1,quant_pecas);
    int control1 = 0;
    int control2=0;
    //Texture2D tabuleiro = LoadImage("/home/devcontainers/dev/Pif_Jogo/teste.png");
    int time_jogando = 1 ;
    
    Texture2D texture = LoadTexture("/home/devcontainers/dev/Pif_Jogo/teste.png");          
    
    SetTargetFPS(60);               
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
            
            //Vector4 jogadores_coord = {jogador1[unity_control].px,jogador1[unity_control].py,jogador2[unity_control].px,jogador2[unity_control].py};
            
            Vector2 coordenadas_peca={jogador1[control1].px,jogador1[control1].py};
            Vector2 coordenadas_peca2={jogador2[control2].px,jogador2[control2].py};
            /*if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                Vector2 AttackPosition = GetMousePosition();
                DrawText(TextFormat("Teste de ataque: %d %d",AttackPosition.x,AttackPosition.y),155,290,15,BLACK);
            }*/

        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        
                /* Definr os limites de movimento, de forma manual para as peças aqui*/
        // Make sure Box B does not go out of move area limits
            
/*

TIME 2:
YMAX = 10
YMIN = 0
X MIN = 25
X MAX = 200

TIME 1:
YMAX = 10
YMIN = 0
X MIN = 25
X MAX = 200

*/           
            int reverse_boundary = 1;
            if (time_jogando == 1){
                if (((coordenadas_peca.x) < table_min_x || (coordenadas_peca.x > table_max_x))  ||  (((coordenadas_peca.y < table_min_y) || (coordenadas_peca.y) > table_max_y)) ) 
                    reverse_boundary = -1;
                movimentopecas(jogador1,control1,reverse_boundary,jogador1[control1].isDame);
                jogador1[control1].isDame = virar_rainha(jogador1,control1,barreiras);
                //ataque_pecas(jogador1,control1,reverse_boundary);
                
                /*typedef struct{
                    pecas *player1; 
                    pecas *player2; 
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
                //ataque_pecas(jogador2,control2,reverse_boundary);
                colisao_pecas(jogador2,jogador1,coordenadas_peca2,control2,quant_pecas);
                }           
            
        //}
        //----------------------------------------------------------------------------------
        
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(texture, 0, 0 , WHITE);

            for(int u_c = 0;u_c<quant_pecas;u_c++){
                DrawRectangle(5*(jogador1[u_c].px), 5*(jogador1[u_c].py),width_print,height_print,BLACK);
                DrawText(TextFormat("%c %d",jogador1[u_c].pecas_jogador, u_c), 5*jogador1[u_c].px, 5*jogador1[u_c].py, height_print, WHITE);
            }
            for(int u_c2=0;u_c2<quant_pecas;u_c2++){
                DrawRectangle(5*(jogador2[u_c2].px), 5*(jogador2[u_c2].py),width_print,height_print,DARKGRAY);
                DrawText(TextFormat("%c %d",jogador2[u_c2].pecas_jogador, u_c2), 5*jogador2[u_c2].px, 5*jogador2[u_c2].py, height_print, WHITE);
            }


            DrawText("Digite a peça que você quer, depois use o teclado para mover. Selecione T para dar a vez ao outro jogador", 0, 30, 15, BLACK);

            //ataque_pecas(jogador1,control1,reverse_boundary);

            DrawText(TextFormat("Peca %d: time: %d, x= %d, y=%d",control1,1,jogador1[control1].px,jogador1[control1].py),0,90,15,BLACK);
            if (time_jogando == -1)
                DrawText("Jogador 2!",0,290,15,BLACK);
            if (time_jogando == 1)
                DrawText("Jogador 1!",0,290,15,BLACK);

            DrawText(TextFormat("Peca %d: time: %d, x= %d, y=%d",control2,-1,jogador2[control2].px,jogador2[control2].py),0,150,15,BLACK);
            EndDrawing();
        //----------------------------------------------------------------------------------
        }   
        //----------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //UnloadImage(tabuleiro);
    UnloadTexture(texture);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}