#include <stdio.h>
#include <stdlib.h>
#include "math_game.h"
#include "raylib.h"
#include <math.h>

#define power2(A) ((A)*(A))

float distance_2_points(Vector4 jogadores_coordenadas){
    return (sqrt(power2(jogadores_coordenadas.x-jogadores_coordenadas.z) + power2(jogadores_coordenadas.y-jogadores_coordenadas.w)));
}
