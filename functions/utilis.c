#include <stdio.h>
#include <stdlib.h>
#include <include/raylib/src/raylib.h>
#include <utilis.h>

typedef struct{
    char pecas_jogador;
    int px;
    int py;
    int vida;
    int defesa;
    int ataque;
    int time;
}pecas;


pecas *allocar_memoria(int quantidade){
    pecas *aux = malloc(quantidade*sizeof(pecas));
    if (aux==NULL) 
        return NULL;
    return aux;
}

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

void setpecas(pecas *jogador, int quant_pecas,int time){
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
