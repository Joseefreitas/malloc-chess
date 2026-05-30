#include "raylib.h"
#include "placar.h"
#include "funcoes_placar.h"
#include "hud.h"

void desenhar_hud(int time_jogando, float timer,placar **head1,placar **head2) {
    int tabuleiro_fim = (GetScreenWidth() + 500) / 2;
    int hudX = tabuleiro_fim + 10;
    int hudY = (GetScreenHeight() - 410) / 2;

    DrawRectangle(hudX, hudY, 300, 400, DARKGRAY);
    DrawRectangleLines(hudX, hudY, 300, 400, BLACK);

    DrawText("PLACAR", hudX + 100, hudY + 20, 25, WHITE);
    DrawText("Pecas mortas do jogador oposto: ",hudX +20,hudY+45,17,WHITE);
    // peça  + pontos jogador 1
    DrawCircle(hudX + 50, hudY + 100, 25, BLACK);
    placar *aux1 = *head1;
    DrawText(TextFormat("J1: %d", aux1->numero), hudX + 90, hudY + 85, 22, WHITE);

    // peça  + pontos jogador 2
    DrawCircle(hudX + 50, hudY + 170, 25, GRAY);
    placar *aux2 = *head2;
    DrawText(TextFormat("J2: %d", aux2->numero), hudX + 90, hudY + 155, 22, WHITE);

    // separador
    DrawLine(hudX + 20, hudY + 220, hudX + 280, hudY + 220, WHITE);

    // vez do jogador
    DrawText("VEZ:", hudX + 20, hudY + 240, 20, WHITE);
    if (time_jogando == 1)
        DrawCircle(hudX + 120, hudY + 250, 18, BLACK);
    else
        DrawCircle(hudX + 120, hudY + 250, 18, GRAY);

    // timer
    DrawText(TextFormat("Tempo: %.0fs", timer), hudX + 20, hudY + 300, 20, WHITE);
}