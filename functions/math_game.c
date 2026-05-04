#include <stdio.h>
#include <stdlib.h>
#include <math_game.h>

int distance_2_points(int x1, int x2,int y1,int y2){
    return (sqrt(power2(x2-x1) + power2(y2-y1)));
}
