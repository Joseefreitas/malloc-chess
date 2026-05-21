#include "tabuleiro.h"

void desenhar_tabuleiro(void) {
    int tamanho_casa = 100;
    int tamanho_tabuleiro = tamanho_casa * 8;
    int offsetX = (GetScreenWidth() - tamanho_tabuleiro) / 2;
    int offsetY = (GetScreenHeight() - tamanho_tabuleiro) / 2;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((x + y) % 2 == 0)
                DrawRectangle(offsetX + x * tamanho_casa, offsetY + y * tamanho_casa, tamanho_casa, tamanho_casa, BEIGE);
            else
                DrawRectangle(offsetX + x * tamanho_casa, offsetY + y * tamanho_casa, tamanho_casa, tamanho_casa, DARKBROWN);
        }
    }
}