#include "tabuleiro.h"
#include "constants.h"

void desenhar_tabuleiro(void) {
    int tamanho_casa = 135;
    //int tamanho_casa = 85; 
    int tamanho_tabuleiro = tamanho_casa * 6;
    int offsetX = wall_distance *((table_min_x)/tamanho_casa);
    int offsetY = wall_distance*((table_min_y)/tamanho_casa);
    if (iniciar==1.0){
        for (int y = 0; y <(tamanho_tabuleiro/tamanho_casa); y++) {
            for (int x = 0; x < (tamanho_tabuleiro/tamanho_casa); x++) {
                if ((x + y) % 2 == 0)
                    DrawRectangle(wall_distance *offsetX + x * tamanho_casa ,wall_distance* offsetY + y * tamanho_casa, tamanho_casa, tamanho_casa, BEIGE);
                //DrawRectangle(offsetX + x * tamanho_casa, offsetY + y * tamanho_casa,width_print,height_print,BEIGE);   
                else
                    DrawRectangle(wall_distance* offsetX + x * tamanho_casa,wall_distance* offsetY + y * tamanho_casa, tamanho_casa, tamanho_casa, DARKBROWN);
                //DrawRectangle(offsetX + x * tamanho_casa, offsetY + y * tamanho_casa,width_print,height_print,DARKBROWN);   

            }
        }
    }
}
